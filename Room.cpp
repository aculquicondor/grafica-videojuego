#include "Room.h"

GLfloat Room::ambient[4] = {.5, .5, .5,1};
GLfloat Room::diffuse[4] = {0.6,0.6,0.6,1};

Room::Room(GLuint texture) : _seen(false), random_engine(std::random_device()()), texture(texture) {
    for (int i = 0; i < 4; ++i)
        this->doors[i] = 0;

    int num_enemies = std::uniform_int_distribution<int>(0, 4)(random_engine);
    for (int i = 0; i < num_enemies; ++i) {
        float x = std::uniform_real_distribution<float>(-width + 1, width - 1)(random_engine),
              z = std::uniform_real_distribution<float>(-width + 1, width - 1)(random_engine);
        int type = std::uniform_int_distribution<int>(0, 2)(random_engine);
        if (type == 0)
            enemies.push_back(new Raticate(glm::vec3(x, 0, z),1));
        else if (type == 1)
            enemies.push_back(new Golem(glm::vec3(x, 0, z),1));
        else
            enemies.push_back(new Arbok(glm::vec3(x, 0, z),1));
    }
}


Room::~Room() {
}


void Room::setDoor(int id, bool value) {
    doors[id] = value;
}


bool Room::getDoor(int id) {
    return doors[id];
}

RoomWhere Room::where(float x, float z, float radius) const {
    if (x + radius > Room::width) {
        if (doors[1] and abs(z) < doorWidth)
            return E_DOOR;
        return E_COLLISION;
    } if (x - radius < -Room::width) {
        if (doors[3] and abs(z) < doorWidth)
            return W_DOOR;
        return W_COLLISION;
    } if (z + radius > Room::width) {
        if (doors[2] and abs(x) < doorWidth)
            return S_DOOR;
        return S_COLLISION;
    } if (z - radius < -Room::width) {
        if (doors[0] and abs(x) < doorWidth)
            return N_DOOR;
        return N_COLLISION;
    }

    return CAN_BE;
}

int Room::playerCollision(glm::vec3 playerPos, float r) {
    for (Enemy *enemy : enemies) {
        glm::vec3 p = enemy->position();
        if (glm::length(glm::distance(p, playerPos)) < enemy->radius() + r) {
            if (enemy->type() == 4)
                enemy->receiveImpact(1);
            return enemy->getPower();
        }
    }
    return 0;
}

int Room::bulletCollision(Enemy *e) {
    if (e->getLifePoints() <= 0 )
        return 0;
    for (Enemy *other_enemy : enemies){
        if (other_enemy != e and other_enemy->type() == 4 and other_enemy->getLifePoints() > 0) {
            glm::vec3 p = other_enemy->position();
            if (glm::length(glm::distance(other_enemy->position(), e->position())) < other_enemy->radius() + e->radius()){
                other_enemy->receiveImpact(1);
                return other_enemy->getPower();
            }
        }
    }
    return 0;
}

bool Room::enemiesCollision(Enemy *e, glm::vec3 nextPos) {
    /*evitar q los enemigos se transpasen*/
    if (e->type() == 4)
        return false;
    for (Enemy *other_enemy : enemies){
        if (other_enemy != e and other_enemy->type() != 4) {
            glm::vec3 p = other_enemy->position();
            if (glm::length(glm::distance(other_enemy->position(), nextPos)) < other_enemy->radius() + e->radius())
                return true;
        }
    }
    return false;
}

void Room::update(float time, glm::vec3 player_pos, float player_radius) {
    /*CREACION DE BALAS*/
    for (Enemy *enemy : enemies){
        if (enemy->type() == 3 and ((Arbok*)enemy)->isShooting()){ // Arbok, puede tener una bala
            glm::vec3 dirBullet = glm::normalize(player_pos - enemy->position());
            glm::vec3 posBullet = enemy->position() + dirBullet * enemy->radius() * 2.0f;
            enemies.push_back(new Bullet(posBullet,dirBullet,0,enemy->getPower()*2,enemy->radius()));
        } // otro enemigo dispara 8 balas
    }

    /*REBOTE EN LAS PAREDES */
    for (Enemy *enemy : enemies) {
        glm::vec3 nextpos = enemy->stepTest(time, player_pos);
        RoomWhere npos = where(nextpos.x, nextpos.z, enemy->radius());
        if (npos == CAN_BE and !enemiesCollision(enemy,nextpos)){
            enemy->step();
        }
        else if (npos == E_COLLISION or npos == W_COLLISION)
            enemy->reflectDirection(-1,1);
        else if (npos == N_COLLISION or npos == S_COLLISION)
            enemy->reflectDirection(1,-1);
        else if (npos > CAN_BE and enemy->type() == 4)
            enemy->receiveImpact(1);
    }

    /*calcular colisiones de las balas*/
    for (Enemy *enemy : enemies) {
        int damage = bulletCollision(enemy);
        if (damage>0)
            enemy->receiveImpact(damage);
    }

    removeDead();
}

void Room::removeDead() {
    for (int i=0 ; i<enemies.size() ; ++i){
        if (enemies[i]->getLifePoints() <= 0){
            enemies.erase(enemies.begin()+i);
            --i;
        }
    }
}

void Room::createBullet(glm::vec3 pos, glm::vec3 dir, int type, int power, float r) {
    if (type == 3){
        glm::vec3 vec1 = glm::rotateY(dir,0.3f);
        glm::vec3 vec2 = glm::rotateY(dir,-0.3f);
        enemies.push_back(new Bullet(pos,vec1,type,(int)(power*0.7), r));
        enemies.push_back(new Bullet(pos,vec2,type,(int)(power*0.7), r));
    }else
        enemies.push_back(new Bullet(pos,dir,type,power, r));
}

const float Room::width = 15;

const float Room::doorWidth = .8f;

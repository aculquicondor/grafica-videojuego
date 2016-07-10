#include "Room.h"

GLfloat Room::ambient[4] = {.5, .5, .5,1};
GLfloat Room::diffuse[4] = {0.6,0.6,0.6,1};

Room::Room(GLuint texture) : _seen(false), random_engine(std::random_device()()), texture(texture) {
    for (int i = 0; i < 4; ++i)
        this->doors[i] = 0;
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

    for (Enemy *enemy : enemies) { //cofres
        if (enemy->type()==5 and collition(enemy->position(),glm::vec3(x,0,z),enemy->radius(),radius)) {
            return COLLISION;
        }
    }
    return CAN_BE;
}

int Room::playerCollision(glm::vec3 playerPos, float r) {
    for (Enemy *enemy : enemies) {
        if (collition(enemy->position(),playerPos,enemy->radius(),r)) {
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
    for (Enemy *other_enemy : enemies)
        if (other_enemy != e and other_enemy->type() == 4 and other_enemy->getLifePoints() > 0)
            if (collition(other_enemy->position(),e->position(),other_enemy->radius(),e->radius())){
                other_enemy->receiveImpact(1);
                return other_enemy->getPower();
            }
    return 0;
}

bool Room::enemiesCollision(Enemy *e, glm::vec3 nextPos) {
    /*evitar q los enemigos se transpasen, no contar las balas*/
    if (e->type() == 4)
        return false;
    for (Enemy *other_enemy : enemies){
        if (other_enemy != e and other_enemy->type() != 4) {
            glm::vec3 p = other_enemy->position();
            return collition(other_enemy->position(),nextPos,other_enemy->radius(),e->radius());
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
        if (npos == CAN_BE  and !enemiesCollision(enemy,nextpos))
            enemy->step();
        else if(npos == COLLISION and enemy->type() == 4)
            enemy->step();
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

void Room::generateEnemies(int lv,bool type) {
    if (type){// salida, hay 1 boss
        int t = std::uniform_int_distribution<int>(0, 3)(random_engine); //tipo de enemigo
        if (t == 0)
            enemies.push_back(new Raticate(generatePosition(Raticate::radio),lv+5));
        else if (t == 1)
            enemies.push_back(new Golem(generatePosition(Golem::radio),lv+5));
        else if (t== 2)
            enemies.push_back(new Arbok(generatePosition(Arbok::radio),lv+5));

    }else{
        int num_enemies = std::uniform_int_distribution<int>(1, 4)(random_engine);
        for (int i = 0; i < num_enemies; ++i) {
            int l = std::uniform_int_distribution<int>(0, 3)(random_engine); //level aleatorio
            int t = std::uniform_int_distribution<int>(0, 3)(random_engine); //tipo de enemigo
            if (t == 0)
                enemies.push_back(new Raticate(generatePosition(Raticate::radio),lv+l));
            else if (t == 1)
                enemies.push_back(new Golem(generatePosition(Golem::radio),lv+l));
            else if (t== 2)
                enemies.push_back(new Arbok(generatePosition(Arbok::radio),lv+l));
            else
            enemies.push_back(new TreasureChest(generatePosition(Arbok::radio)));
        }
    }
}

glm::vec3 Room::generatePosition(float r) {
    glm::vec3 newPos= {0,0,0};
    if (enemies.empty()){
        newPos.x = std::uniform_real_distribution<float>(-width*0.5f, width*0.5f)(random_engine);
        newPos.z = std::uniform_real_distribution<float>(-width*0.5f, width*0.5f)(random_engine);
        return newPos;
    }

    int i = 0;
    while(i != enemies.size()){
        newPos.x = std::uniform_real_distribution<float>(-width*0.5f, width*0.5f)(random_engine);
        newPos.z = std::uniform_real_distribution<float>(-width*0.5f, width*0.5f)(random_engine);
        for (i=0 ; i<enemies.size() and !collition(enemies[i]->position(),newPos,enemies[i]->radius(),r); ++i){}
    };
    return newPos;
}

bool Room::collition(glm::vec3 pos1, glm::vec3 pos2, float r1, float r2) const {
    return glm::length(glm::distance(pos1, pos2)) <= r1+r2;
}

void Room::generateItems() { }

const float Room::width = 15;

const float Room::doorWidth = .8f;

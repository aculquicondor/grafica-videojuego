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

RoomWhere Room::where(float x, float z, float radius, Enemy *enemy) const {
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
    for (Enemy *other_enemy : enemies)
        if (other_enemy != enemy) {
            glm::vec3 p = other_enemy->position();
            if (glm::length(glm::distance(p, glm::vec3(x, 0, z))) < other_enemy->radius() + radius)
                return COLLISION;
        }
    return CAN_BE;
}

void Room::update(float time, glm::vec3 player_pos, float player_radius) {
    for (Enemy *enemy : enemies){
        if (enemy->type() == 3 and ((Arbok*)enemy)->isShooting()){ // Arbok, puede tener una bala
            glm::vec3 dirBullet = glm::normalize(player_pos - enemy->position());
            glm::vec3 posBullet = enemy->position() + dirBullet * enemy->radius() * 2.0f;
            enemies.push_back(new Bullet(posBullet,dirBullet,0,enemy->getPower()*2));
        } // otro enemigo dispara 8 balas
    }
    for (Enemy *enemy : enemies) {
        glm::vec3 pos = enemy->stepTest(time, player_pos);
        RoomWhere npos = where(pos.x, pos.z, enemy->radius(), enemy);
        if (npos == CAN_BE)
            enemy->step();
        else if (npos == E_COLLISION or npos == W_COLLISION)
            enemy->reflectDirection(-1,1);
        else if (npos == N_COLLISION or npos == S_COLLISION)
            enemy->reflectDirection(1,-1);
    }

    for (int i=0 ; i<enemies.size() ; ++i){
        if (enemies[i]->getLifePoints()<=0){
            enemies.erase(enemies.begin()+i);
            --i;
        }
    }
}

const float Room::width = 15;

const float Room::doorWidth = .8f;

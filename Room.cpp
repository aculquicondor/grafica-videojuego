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
            enemies.push_back(new Raticate(glm::vec3(x, 0, z)));
        else if (type == 1)
            enemies.push_back(new Golem(glm::vec3(x, 0, z)));
        else
            enemies.push_back(new Arbok(glm::vec3(x, 0, z)));
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
        return CANT_BE;
    } if (x - radius < -Room::width) {
        if (doors[3] and abs(z) < doorWidth)
            return W_DOOR;
        return CANT_BE;
    } if (z + radius > Room::width) {
        if (doors[2] and abs(x) < doorWidth)
            return S_DOOR;
        return CANT_BE;
    } if (z - radius < -Room::width) {
        if (doors[0] and abs(x) < doorWidth)
            return N_DOOR;
        return CANT_BE;
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
    for (Enemy *enemy : enemies) {
        glm::vec3 pos = enemy->stepTest(time, player_pos);
        if (where(pos.x, pos.z, enemy->radius(), enemy) == CAN_BE)
            enemy->step();
        else
            enemy->reflectDirection();
    }
}

const float Room::width = 15;

const float Room::doorWidth = .8f;

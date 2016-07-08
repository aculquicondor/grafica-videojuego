#include "Player.h"


GLfloat Player::ambient[4] = {.8f, .8f, 0, 1};
GLfloat Player::diffuse[4] = {.9f, .9f, 0, 1};


Player::Player() :
        x(0), z(0), topDown(0), leftRight(0), mv_x(0), mv_z(0){
    lifePoints = 100;
    defense = 10;
    power = 50;
    goldenKey = 0;
    silverKey = 0;
    speed = 7.5f;
    graceTime = 0;
    dir = glm::vec3(0,0,1);
}

Player::~Player() {

}

glm::vec3 Player::moveTest(float time) {
    nx = x + mv_x * speed * time;
    nz = z + mv_z * speed * time;
    graceTime -= time;
    if (graceTime < 0)
        graceTime = 0;
    return glm::vec3(nx, 0, nz);
}

glm::vec3 Player::move(RoomWhere where) {
    if (where == CAN_BE or where == COLLISION) {
        x = nx;
        z = nz;
    } else if (where == N_DOOR) {
        z = Room::width - radius;
    } else if (where == S_DOOR) {
        z = -Room::width + radius;
    } else if (where == E_DOOR) {
        x = -Room::width + radius;
    } else if (where == W_DOOR) {
        x = Room::width - radius;
    }

    if (mv_x != 0) {
        angle = mv_x * 90;
        angle -= mv_x * mv_z * 45;
        dir.x = mv_x;
        dir.z = mv_z;
    } else if (mv_z != 0) {
        angle = 90 - mv_z * 90;
        dir.x = 0;
        dir.z = mv_z;
    }
    return glm::vec3(x, 0, z);
}


void Player::reset() {
    x = 0;
    z = 0;
    angle = 0;
    lifePoints = 100;
    defense = 10;
    power = 50;
    goldenKey = 0;
    silverKey = 0;
    speed = 7.5f;
}

void Player::specialDown(int key) {
    if (key == GLUT_KEY_UP) {
        mv_z = -1;
        ++topDown;
    } else if (key == GLUT_KEY_DOWN) {
        mv_z = 1;
        ++topDown;
    } else if (key == GLUT_KEY_RIGHT) {
        mv_x = 1;
        ++leftRight;
    } else if (key == GLUT_KEY_LEFT) {
        mv_x = -1;
        ++leftRight;
    }
}

void Player::specialUp(int key) {
    if ((key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) && (--topDown) == 0)
        mv_z = 0;
    else if ((key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) && (--leftRight) == 0)
        mv_x = 0;
}


glm::vec3 Player::position() const {
    return glm::vec3(x, 0, z);
}

void Player::reciveImpact(int d) {
    if (d == 0) return;
    if (graceTime <= 0){
        int damage = d-defense;
        if(damage<1)
            damage = 1;
        lifePoints -= damage;
        graceTime = 1.5;
        std::cout << "life points : "<<lifePoints << std::endl;
    }
}

glm::vec3 Player::direction() {
    return glm::normalize(dir);
}

int Player::getPower() {
    return power;
}

const float Player::radius = 1.f;

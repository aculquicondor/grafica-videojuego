#include "Player.h"

Player::Player() :
        x(0), z(0), topDown(0), leftRight(0),
        model(Model::getModel("pikachu")) {
}

Player::~Player() {
    delete model;
}

RoomWhere Player::move(float time, const Room *room) {
    float nx = x + mv_x * speed * time, nz = z + mv_z * speed * time;
    RoomWhere where = room->where(nx, nz, radius);
    if (where == CAN_BE) {
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
    } else if (mv_z != 0) {
        angle = 90 - mv_z * 90;
    }

    return where;
}


void Player::reset() {
    x = 0;
    z = 0;
    angle = 0;
}

void Player::draw() {
    glPushMatrix();
    glTranslated(x, 0, z);
    glRotated(angle, 0, 1, 0);
    glScalef(.05f, .05f, .05f);
    model->draw();
    glPopMatrix();
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


const float Player::speed = 8.f;
const float Player::radius = 1.f;

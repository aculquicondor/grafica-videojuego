#include "Player.h"

Player::Player() :
        x(0), z(0), topDown(0), leftRight(0),
        model(new Model("models/pikachu.obj")) {
}

Player::~Player() {
    delete model;
}

void Player::draw(float time) {
    x += mv_x * time;
    z += mv_z * time;

    glPushMatrix();
    glTranslated(x, 0, z);
    glScalef(.005f, .005f, .005f);
    model->draw();
    glPopMatrix();
}


void Player::specialDown(int key) {
    if (key == GLUT_KEY_UP) {
        mv_z = -speed;
        ++topDown;
    } else if (key == GLUT_KEY_DOWN) {
        mv_z = speed;
        ++topDown;
    } else if (key == GLUT_KEY_RIGHT) {
        mv_x = speed;
        ++leftRight;
    } else if (key == GLUT_KEY_LEFT) {
        mv_x = -speed;
        ++leftRight;
    }
}

void Player::specialUp(int key) {
    if ((key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) && (--topDown) == 0)
        mv_z = 0;
    else if ((key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) && (--leftRight) == 0)
        mv_x = 0;
}


const float Player::speed = .5f;

#include "Player.h"

Player::Player() : model(new Model("models/pikachu.obj")) {

}

Player::~Player() {
    delete model;
}

void Player::draw() const {
    glPushMatrix();
    glScalef(.001f, .001f, .001f);
    model->draw();
    glPopMatrix();
}

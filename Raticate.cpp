//
// Created by Ed on 08/05/2016.
//

#include "Raticate.h"

Raticate::Raticate(glm::vec3 _pos_actual) :
        model(Model::getModel("raticate")) {
    pos_actual = _pos_actual;
    speed = 3;
}


void Raticate::draw()
{
    glPushMatrix();
    glTranslatef(pos_actual.x, 0, pos_actual.z);
    glScalef(.5f, .5f, .5f);
    glColor3f(.2f, .8f, .2f);
    model->draw();
    glPopMatrix();
}


glm::vec3 Raticate::stepTest(float time, glm::vec3 pos_player)
{
    glm::vec3 vector = pos_player-pos_actual;
    vector = glm::normalize(vector);
    next_pos = pos_actual + vector*speed*time;
    return next_pos;
}


void Raticate::step() {
    pos_actual = next_pos;
}


const float Raticate::radio = 1.f;

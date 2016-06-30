//
// Created by Ed on 08/05/2016.
//

#include "Raticate.h"


GLfloat Raticate::ambient[4] = {.6f, .6f, .2f, 1};
GLfloat Raticate::diffuse[4] = {.7f, .7f, .3f, 1};


Raticate::Raticate(glm::vec3 pos_actual, float speed) :
        speed(speed), pos_actual(pos_actual), angle(0) {
}

glm::vec3 Raticate::stepTest(float time, glm::vec3 pos_player)
{
    glm::vec3 vector = pos_player - pos_actual;
    angle = glm::atan(vector.x, vector.z);
    vector = glm::normalize(vector);
    next_pos = pos_actual + vector * speed * time;
    return next_pos;
}

void Raticate::step() {
    pos_actual = next_pos;
}

void Raticate::reflectDirection() {
    //nothing
}

const float Raticate::radio = 1.f;

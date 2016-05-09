//
// Created by Ed on 08/05/2016.
//

#include "Raticate.h"

Raticate::Raticate(glm::vec3 _pos_actual) :
        model(Model::getModel("raticate")) {
    pos_actual = _pos_actual;
    speed = 4;
}


void Raticate::draw()
{
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(pos_actual.x, 0, pos_actual.z);
    glScalef(.05f, .05f, .05f);
    model->draw();
    glPopMatrix();
}


void Raticate::step(float time, glm::vec3 pos_player)
{
    glm::vec3 vector = pos_player-pos_actual;
    vector = glm::normalize(vector);
    pos_actual += vector*speed*time;
}


const float Raticate::radio = 1.f;

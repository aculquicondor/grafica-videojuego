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


void Raticate::step(float time, glm::vec3 pos_player)
{
    glm::vec3 vector = pos_player-pos_actual;
    vector = glm::normalize(vector);
    pos_actual += vector*speed*time;
}


const float Raticate::radio = 1.f;

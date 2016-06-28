//
// Created by Ed on 08/05/2016.
//

#include "Raticate.h"


GLfloat Raticate::ambient[4] = {.6f, .6f, .2f, 1};
GLfloat Raticate::diffuse[4] = {.7f, .7f, .3f, 1};


Raticate::Raticate(glm::vec3 pos_actual, float speed) :
        speed(speed), pos_actual(pos_actual), angle(0),
        model(Model::getModel("raticate")) {
}


void Raticate::draw()
{
    glPushMatrix();
    glTranslatef(pos_actual.x, 0, pos_actual.z);
    glRotatef(angle * 57.2957f, 0, 1, 0);
    glColor3f(.2f, .8f, .2f);
    glScalef(.4f, .4f, .4f);
    glRotated(90, 1, 0, 0);
    glMaterialfv(GL_FRONT,GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, diffuse);
    model->draw();
    glPopMatrix();
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

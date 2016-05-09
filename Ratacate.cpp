//
// Created by Ed on 08/05/2016.
//

#include "Ratacate.h"

void Ratacate::Ratacate(glm::vec3 _pos_actual)
{
    pos_actual = _pos_actual;
    speed = 4;
}
void Ratacate::Draw()
{

    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(pos_actual[0], pos_actual[1], 0.0);
    glutSolidSphere(radio, 20, 20);
    glPopMatrix();
}
void Ratacate::Step(glm::vec3 pos_player, float time)
{
    glm::vec3 vector = pos_player-pos_actual;
    vector = glm::normalize(vector);
    pos_actual += vector*speed*time;
}


//
// Created by Ed on 08/05/2016.
//

#ifndef VIDEOGAME_RATACATE_H
#define VIDEOGAME_RATACATE_H

#include <glm/glm.hpp>
#include "Enemy.h"


class Raticate : public Enemy
{
public:
    Raticate(glm::vec3 pos_actual, float speed = 3.f);
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 pos_player);
    void step();
    static GLfloat ambient[4];
    static GLfloat diffuse[4];

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return pos_actual;
    }

    float getAngle(){
        return angle;}

    int type() {
        return 1;}
    void reflectDirection();
private:
    float speed;
    float angle;
    glm::vec3 pos_actual, next_pos;
};


#endif //VIDEOGAME_RATACATE_H

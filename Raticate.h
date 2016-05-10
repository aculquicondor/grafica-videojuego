//
// Created by Ed on 08/05/2016.
//

#ifndef VIDEOGAME_RATACATE_H
#define VIDEOGAME_RATACATE_H


#include <cmath>

#include <glm/glm.hpp>
#include <GL/glut.h>

#include "Enemy.h"
#include "Model.h"


class Raticate : public Enemy
{
public:
    Raticate(glm::vec3 pos_actual, float speed = 3.f);
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 pos_player);
    void step();
    void draw();

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return pos_actual;
    }
    void reflectDirection();
private:
    float speed;
    float angle;
    glm::vec3 pos_actual, next_pos;

    Model *model;
};


#endif //VIDEOGAME_RATACATE_H

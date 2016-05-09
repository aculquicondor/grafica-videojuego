//
// Created by Ed on 08/05/2016.
//

#ifndef VIDEOGAME_RATACATE_H
#define VIDEOGAME_RATACATE_H


#include "Enemy.h"
#include <glm/glm.hpp>
#include <GL/glut.h>
#include <math.h>


class Ratacate : Enemy
{
public:
    Ratacate(glm::vec3 _pos_actual);
    static const float radio = 1f;
    glm::vec3 pos_actual;
    void Step(glm::vec3 pos_player, float time);
    void Draw();
    float speed;
    glm::vec3 direction;
};


#endif //VIDEOGAME_RATACATE_H

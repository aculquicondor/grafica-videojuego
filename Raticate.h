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
    Raticate(glm::vec3 _pos_actual);
    static const float radio;
    void step(float time, glm::vec3 pos_player);
    void draw();

private:
    float speed;
    glm::vec3 direction;
    glm::vec3 pos_actual;

    Model *model;
};


#endif //VIDEOGAME_RATACATE_H

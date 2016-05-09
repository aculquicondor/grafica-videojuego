//
// Created by Ed on 08/05/2016.
//
#ifndef VIDEOGAME_GOLEM_H
#define VIDEOGAME_GOLEM_H

#include <random>

#include <GL/glut.h>
#include <glm/glm.hpp>

#include "Enemy.h"
#include "Room.h"


class Golem : Enemy {
public:
    Golem(glm::vec3);

    glm::vec3 position;
    glm::vec3 direction;
    float speed;
    float acumulateT;
    float rolling;

    std::default_random_engine random_engine;
    static const float radio;
    void step(glm::vec3, float, Room *);
    void draw();
    glm::vec3 changeDirection();
    bool colition(Room*, glm::vec3);
};


#endif //VIDEOGAME_GOLEM_H

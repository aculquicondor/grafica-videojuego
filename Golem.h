//
// Created by Ed on 08/05/2016.
//
#ifndef VIDEOGAME_GOLEM_H
#define VIDEOGAME_GOLEM_H

#include <random>

#include <glm/glm.hpp>

#include "Enemy.h"
#include "Room.h"
#include "Model.h"


class Golem : public Enemy {
public:
    Golem(glm::vec3);

    std::default_random_engine random_engine;
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 pos_player);
    void step();
    void draw();

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return cPosition;
    }
    void reflectDirection();
private:
    void changeDirection();
    float speed;
    float countDown;
    bool rolling;
    glm::vec3 cPosition, nPosition;
    glm::vec3 direction;
    Model *model;
};

#endif //VIDEOGAME_GOLEM_H

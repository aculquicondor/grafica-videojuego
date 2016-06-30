//
// Created by Ed on 08/05/2016.
//
#ifndef VIDEOGAME_GOLEM_H
#define VIDEOGAME_GOLEM_H

#include <random>
#include <glm/glm.hpp>

#include "Enemy.h"
#include "Room.h"


class Golem : public Enemy {
public:
    Golem(glm::vec3);

    std::default_random_engine random_engine;
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 pos_player);
    void step();
    static GLfloat ambient[4];
    static GLfloat diffuse[4];

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return cPosition;
    }

    float getAngle(){
        return glm::atan(direction.x, direction.z);
    }

    void reflectDirection();

    int type() {
        return 2;}
private:
    void changeDirection();
    float speed;
    float countDown;
    bool rolling;
    glm::vec3 cPosition, nPosition;
    glm::vec3 direction;


};

#endif //VIDEOGAME_GOLEM_H

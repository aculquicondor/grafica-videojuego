//
// Created by Ed on 09/05/2016.
//
#ifndef VIDEOGAME_ARBOK_H
#define VIDEOGAME_ARBOK_H

#include <random>

#include <glm/glm.hpp>

#include "Enemy.h"
#include "Room.h"
#include "Model.h"

struct Bullet{
    glm::vec3 position, direction;
    bool alive;
    float speed;
    float radio;
};

class Arbok : public Enemy
{
public:
    Arbok(glm::vec3);

    std::default_random_engine random_engine;
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 playerPosition);
    void draw();

    void step();

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return cPosition;
    }
    void reflectDirection();

private:
    Model *model;
    glm::vec3 cPosition, nextpos;;
    glm::vec3 direction;
    float speed;
    float acumulateT;
    bool shooting;
    void changeDirection();
    Bullet bullet;
    void settingBullet(glm::vec3,glm::vec3);
    void resetBullet();
    bool bulletColition();

    static GLfloat ambient[4];
    static GLfloat diffuse[4];
};


#endif //VIDEOGAME_ARBOK_H

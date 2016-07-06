//
// Created by Ed on 09/05/2016.
//
#ifndef VIDEOGAME_ARBOK_H
#define VIDEOGAME_ARBOK_H

#include <random>
#include <glm/glm.hpp>

#include "Enemy.h"
#include "Bullet.h"
#include "Room.h"

class Arbok : public Enemy
{
public:
    Arbok(glm::vec3, int);
    ~Arbok();

    std::default_random_engine random_engine;
    static const float radio;
    glm::vec3 stepTest(float time, glm::vec3 playerPosition);
    static GLfloat ambient[4];
    static GLfloat diffuse[4];

    void step();

    float radius() const {
        return radio;
    }

    glm::vec3 position() const {
        return cPosition;
    }
    float getAngle(){
        return glm::atan(direction.x, direction.z);
    }

    int type() {
        return 3;}

    float* getAmbient() {
        return ambient;
    }
    float* getdiffuse() {
        return diffuse;
    }

    void reflectDirection(float, float);
    bool isShooting();
    int getPower();
    int getLifePoints();

private:
    glm::vec3 cPosition, nextpos;;
    glm::vec3 direction;
    bool myShot;
    float speed;
    float acumulateT;
    float shootingTime;
    void changeDirection();

    int lifePoints;
    int defense;
    int power;
    int level;
};


#endif //VIDEOGAME_ARBOK_H

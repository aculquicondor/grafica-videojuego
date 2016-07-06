#ifndef VIDEOGAME_ENEMY_H
#define VIDEOGAME_ENEMY_H

#include <glm/vec3.hpp>
#include "Model.h"

class Enemy {
public:
    virtual glm::vec3 stepTest(float time, glm::vec3 playerPosition) = 0;
    virtual void step() = 0;
    virtual float radius() const = 0;
    virtual glm::vec3 position() const = 0;
    virtual void reflectDirection(float,float) = 0;
    virtual float getAngle() = 0;
    virtual int type() = 0;
    virtual int getLifePoints() = 0;
    virtual int getPower() = 0;
    //virtual void receiveImpact(int) = 0;
};


#endif //VIDEOGAME_ENEMY_H

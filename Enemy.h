#ifndef VIDEOGAME_ENEMY_H
#define VIDEOGAME_ENEMY_H

#include "Player.h"


class Enemy {
public:
    virtual void step(float time, glm::vec3 playerPosition) = 0;
    virtual void draw() = 0;
};


#endif //VIDEOGAME_ENEMY_H

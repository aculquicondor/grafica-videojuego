//
// Created by Ed on 08/05/2016.
//
#define GLM_FORCE_RADIANS
#ifndef VIDEOGAME_GOLEM_H
#define VIDEOGAME_GOLEM_H

#include <random>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Enemy.h"
#include "Room.h"


class Golem : public Enemy {
public:
    Golem(glm::vec3, int);
    ~Golem();

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

    void reflectDirection(float,float);

    int type() { return 2;}
    int getPower();
    int getLifePoints();
    void receiveImpact(int);
    void createItem(int typeItem);
    Item* getItem();

private:
    void changeDirection();
    float speed;
    float countDown;
    bool rolling;
    glm::vec3 cPosition, nPosition;
    glm::vec3 direction;
    int lifePoints;
    int defense;
    int power;
    int level;
    Item* myItem;
};

#endif //VIDEOGAME_GOLEM_H

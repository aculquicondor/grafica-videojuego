//
// Created by jasillo on 05/07/16.
//

#ifndef VIDEOGAME_BULLET_H
#define VIDEOGAME_BULLET_H


#include "Enemy.h"
#include "Room.h"

class Bullet : public Enemy{
private:
    glm::vec3 cPosition, direction, nextpos;
    //bool alive;
    float speed;
    /* tipo 0 no rebota
       tipo 1 rebota*/
    bool bounce;
    int power;
    int lifePoints;
public:
    Bullet(glm::vec3, glm::vec3, int, int);
    ~Bullet();
    glm::vec3 stepTest(float time, glm::vec3 playerPosition);
    void step();
    void reflectDirection(float,float);

    static const float radio;
    float radius() const{
        return radio;
    }
    glm::vec3 position() const {
        return cPosition;
    }
    float getAngle() {
        return 0;
    }
    int type() {
        return 4;
    }
    int getPower();
    int getLifePoints();
    void receiveImpact(int);
};




#endif //VIDEOGAME_BULLET_H

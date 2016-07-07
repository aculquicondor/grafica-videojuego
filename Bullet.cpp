//
// Created by jasillo on 05/07/16.
//

#include "Bullet.h"
Bullet::Bullet(glm::vec3 initial, glm::vec3 dir, int type, int p):
                                                    cPosition(initial),
                                                    power(p),
                                                    direction(dir){
    if (type == 0){//normal sin rebote
        speed = 8;
        bounce = false;
    } else if (type == 1){//normal con rebote
        speed = 8;
        bounce = true;
    } else{ // rapido sin rebote
        speed = 12.0;
        bounce = false;
    }
    lifePoints = 1;
}

Bullet::~Bullet() {

}

glm::vec3 Bullet::stepTest(float time, glm::vec3 playerPosition) {
    nextpos = cPosition + direction * speed * time;
    return nextpos;
}

void Bullet::step()
{
    cPosition = nextpos;
}

void Bullet::reflectDirection(float x, float z) {
    if (bounce){
        direction.x *= x;
        direction.z *= z;
    }else
        lifePoints = 0;
}

int Bullet::getPower() {
    return power;
}

int Bullet::getLifePoints() {
    return lifePoints;
}

void Bullet::receiveImpact(int damage) {
    lifePoints -= damage;
}

const float Bullet::radio = 0.5f;
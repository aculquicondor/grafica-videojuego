//
// Created by jasillo on 05/07/16.
//

#include "Bullet.h"
Bullet::Bullet(glm::vec3 initial, glm::vec3 dir, int type, int p, float r): direction(dir){

    cPosition = initial + dir * (r+radio+0.25f);
    if (type == 0){//normal sin rebote
        speed = 7;
        bounce = false;
    } else if (type == 1){//normal con rebote
        speed = 10;
        bounce = true;
    } else if (type == 2){ // rapido sin rebote
        speed = 15.0;
        bounce = false;
    } else if (type == 3){ // tiro doble
        speed = 10.0;
        bounce = false;
    }
    power = p;
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
    lifePoints = 0;
}

Item* Bullet::getItem() {
    return nullptr;
}

const float Bullet::radio = 0.5f;
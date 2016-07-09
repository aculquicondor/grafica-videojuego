//
// Created by Ed on 08/05/2016.
//

#include "Golem.h"


GLfloat Golem::ambient[4] = {.45f, .5f, .3f, 1.f};
GLfloat Golem::diffuse[4] = {.5f, .55f, .35f, 1.f};


Golem::Golem(glm::vec3 pos, int lv):
        cPosition(pos),
        countDown(1.5),
        level(lv),
        random_engine(std::random_device()()),
        rolling(false){
    // base + nivel*constante
    speed = 2.0f + lv * 0.25f;
    power = 10 + lv * 5;
    defense = 20 + lv * 10;
    lifePoints = 200 + lv * 40;
    changeDirection();
}

glm::vec3 Golem::stepTest(float time, glm::vec3 playerPosition)
{
    countDown -= time;
    if (rolling){ // rodando
        if (countDown <= 0){
            changeDirection();
            countDown = 1.5;
            speed = 2.0f + level * 0.25f;
            power = 10 + level * 5;
            defense = 20 + level * 10;
            rolling = false;
        }
    }else{ // caminando
        if (countDown <= 0){
            changeDirection();
            countDown = 1.5;
        }
        //  golem vision
        if(glm::length(glm::distance(playerPosition, cPosition)) < 10.0) {
            glm::vec3 vector1 = glm::normalize(playerPosition-cPosition);
            glm::vec3 vector2 = glm::normalize(direction);
            if(glm::angle(vector1,vector2) < 1.5708) //90º de visionen promedio
            {
                rolling = true;
                speed = 10.0f + level * 0.5f;
                power = 20 + level * 10;
                defense = 10 + level * 5;
                countDown = 3;
                direction =glm::normalize(playerPosition-cPosition);
            }
        }
    }
    nPosition = this->position()+direction * speed * time;
    return nPosition;
}

void Golem::step() {
    cPosition = nPosition;
}

void Golem::changeDirection() {
    glm::vec3 dir;
    dir[0] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    dir[1] = 0;
    dir[2] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    direction = glm::normalize(dir);
}

void Golem::reflectDirection(float x, float z) {
    direction.x *= x;
    direction.z *= z;
}

int Golem::getPower() {
    return power;
}

int Golem::getLifePoints() {
    return lifePoints;
}

void Golem::receiveImpact(int d) {
    int damage = d-defense;
    if (damage<1)
        damage = 1;
    lifePoints -= damage;
}

const float Golem::radio = 1.f;
//
// Created by Ed on 09/05/2016.
//

#include "Arbok.h"

GLfloat Arbok::ambient[4] = {.45f, .1f, .5f, 1.f};
GLfloat Arbok::diffuse[4] = {.47f, .12f, .52f, 1.f};


Arbok::Arbok(glm::vec3 pos, int lv):
        cPosition(pos),
        level(lv),
        speed(3),
        acumulateT(0),
        //bullet(nullptr),
        shootingTime(0),
        myShot(false),
        random_engine(std::random_device()()){

    // base + nivel*constante
    speed = 2.0f + lv * 0.2f;
    power = 20 + lv * 10;
    defense = 15 + lv * 8;
    lifePoints = 150 + lv * 30;
    changeDirection();
}

Arbok::~Arbok() {

}

glm::vec3 Arbok::stepTest(float time, glm::vec3 playerPosition) {

    acumulateT -= time;
    nextpos = cPosition + direction * speed * time;

    if (acumulateT <= 0)
    {
        changeDirection();
        acumulateT = 1.5;
    }
    if (shootingTime == 0) {
        if (glm::length(glm::distance(playerPosition, cPosition)) < 15.0) {

            float angle1 = glm::atan(direction.z,direction.x); //vision
            float angle2 = glm::atan(playerPosition.z-direction.z,playerPosition.x-direction.x);
            float dist1 = glm::abs(angle1-angle2);
            float dist2 = 2*3.14159f - dist1;
            if (dist1 < .9 or dist2 < .9) //90º de visionen promedio
            {
                shootingTime = 2.0;
                myShot = true;
            }else
                shootingTime = 0;
        }
    } else
        shootingTime -= time;
    if (shootingTime < 0)
        shootingTime = 0;
    return nextpos;
}

void Arbok::changeDirection()
{
    glm::vec3 dir;
    dir[0] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    dir[1] = 0;
    dir[2] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    direction = glm::normalize(dir);
}


void Arbok::step()
{
    cPosition = nextpos;
}

void Arbok::reflectDirection(float x, float z){
    direction.x *= x;
    direction.z *= z;
    acumulateT = 1.5;
}

bool Arbok::isShooting() {
    if (myShot){
        myShot = false;
        return true;
    }
    return false;
}

int Arbok::getPower() {
    return power;
}

int Arbok::getLifePoints() {
    return lifePoints;
}
const float Arbok::radio = 1.f;
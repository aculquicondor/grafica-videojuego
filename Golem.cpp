//
// Created by Ed on 08/05/2016.
//

#include "Golem.h"


GLfloat Golem::ambient[4] = {.45f, .5f, .3f, 1.f};
GLfloat Golem::diffuse[4] = {.5f, .55f, .35f, 1.f};


Golem::Golem(glm::vec3 pos):
        cPosition(pos),
        speed(2),
        countDown(1.5),
        random_engine(std::random_device()()),
        rolling(false){
    changeDirection();
}

glm::vec3 Golem::stepTest(float time, glm::vec3 playerPosition)
{
    countDown -= time;
    if (rolling){ // rodando
        if (countDown <= 0){
            changeDirection();
            countDown = 1.5;
            speed = 2;
            rolling = false;
        }
    }else{ // caminando
        if (countDown <= 0){
            changeDirection();
            countDown = 1.5;
        }
        //  golem vision
        if(glm::length(glm::distance(playerPosition, cPosition)) < 10.0) {
            float angle1 = glm::atan(direction.z,direction.x); //vision
            float angle2 = glm::atan(playerPosition.z-direction.z,playerPosition.x-direction.x);
            float dist1 = glm::abs(angle1-angle2);
            float dist2 = 2*3.14159f - dist1;
            if(dist1<.9 or dist2<.9) //90º de visionen promedio
            {
                rolling = true;
                speed =  12;
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

void Golem::reflectDirection() {
    if (nPosition.x + radio > Room::width)
        direction.x *= -1;
    if (nPosition.x - radio < -Room::width)
        direction.x *= -1;
    if (nPosition.z + radio > Room::width)
        direction.z *= -1;
    if (nPosition.z - radio < -Room::width)
        direction.z *= -1;
}

const float Golem::radio = 1.f;
//
// Created by Ed on 09/05/2016.
//

#include "Arbok.h"

GLfloat Arbok::ambient[4] = {.45f, .1f, .5f, 1.f};
GLfloat Arbok::diffuse[4] = {.47f, .12f, .52f, 1.f};


Arbok::Arbok(glm::vec3 pos):
        cPosition(pos),
        speed(3),
        acumulateT(0),
        random_engine(std::random_device()()){
    changeDirection();
    resetBullet();
}

glm::vec3 Arbok::stepTest(float time, glm::vec3 playerPosition) {

    acumulateT -= time;
    nextpos = cPosition + direction * speed * time;

    if (acumulateT <= 0)
    {
        changeDirection();
        acumulateT = 1.5;
    }

    if (!bullet.alive) //no disparo
    {
        //vision arbok
        if (glm::length(glm::distance(playerPosition, cPosition)) < 10.0) {
            float angle1 = (float) atan2(direction.z, direction.x); //vision
            float angle2 = (float) atan2(playerPosition.z - direction.z, playerPosition.x - direction.x);
            float dist1 = glm::abs(angle1 - angle2);
            float dist2 = 2 * 3.14159f - dist1;
            if (dist1 < .9 or dist2 < .9) //90º de visionen promedio
                settingBullet(cPosition, glm::normalize(playerPosition-cPosition));
        }
    }else//disparo
    {
        bullet.position += bullet.direction*(bullet.speed*time);
        if (bulletColition())
            resetBullet();
    }
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

void Arbok::reflectDirection(){

}

void Arbok::settingBullet(glm::vec3 pos, glm::vec3 dir) {
    bullet.alive = true;
    bullet.position = pos;
    bullet.direction = dir;
}

void Arbok::resetBullet() {
    bullet.position = glm::vec3(0,0,0);
    bullet.direction = glm::vec3(0,0,0);;
    bullet.alive = false;
    bullet.speed = 17.0;
    bullet.radio = 0.25;
}

bool Arbok::bulletColition(){
    if (bullet.position.x + bullet.radio > Room::width)
        return true;
    if (bullet.position.x - bullet.radio < -Room::width)
        return true;
    if (bullet.position.z + bullet.radio > Room::width)
        return true;
    if (bullet.position.z - bullet.radio < -Room::width)
        return true;
    return false;
}

const float Arbok::radio = 1.f;
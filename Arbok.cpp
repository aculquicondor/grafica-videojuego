//
// Created by Ed on 09/05/2016.
//

#include "Arbok.h"


Arbok::Arbok(glm::vec3 pos):
        cPosition(pos),
        speed(3),
        acumulateT(0),
        random_engine(std::random_device()()),
        model(Model::getModel("arbok"))
{
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

void Arbok::draw()
{
    glPushMatrix();
    glTranslatef(cPosition.x, 0.0, cPosition.z);
    glScalef(.25f, .25f, .25f);
    glColor3f(.2f, 0, .5f);
    glRotatef(glm::atan(direction.x, direction.z) * 57.2957f, 0, 1, 0);
    glRotatef(40,1,0,0);
    model->draw();
    glPopMatrix();

    if (bullet.alive){
        glPushMatrix();
        glTranslatef(bullet.position.x,0, bullet.position.z);
        glColor3f(1, 1, 1);
        glutSolidSphere(bullet.radio,10,10);
        glPopMatrix();
    }
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
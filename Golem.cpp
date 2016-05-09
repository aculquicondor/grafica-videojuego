//
// Created by Ed on 08/05/2016.
//

#include "Golem.h"


Golem::Golem(glm::vec3 pos): position(pos), speed(3), acumulateT(0),
                             random_engine(std::random_device()()), rolling(0) {

}

void Golem::draw() {
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(position[0], position[1], position[2]);
    glutSolidSphere(radio, 20, 20);
    glPopMatrix();
}

void Golem::step(glm::vec3 playerPosition, float time, Room* room) {
    if (rolling <= 0) //caminando
    {
        acumulateT+=time;
        if (acumulateT > 1)
            direction = changeDirection();
        //vision golem
        float dist = sqrt(pow(playerPosition[0]-position[0],2)+pow(playerPosition[2]-position[2],2));
        if(dist < 5.0) {
            float angle = atan2(direction[2],direction[0]);
            float anglePlayer = atan2(playerPosition[2],playerPosition[0]);
            if(anglePlayer < angle + 15.0 && anglePlayer > angle - 15.0)
            {
                rolling = 3;
                speed =  10;
            }
        }
        glm::vec3 npos = direction * speed * time;
        if (colition(room,npos))
            acumulateT = 1;

    }else{ //rodando
        rolling -=time;
        acumulateT = 0;
        glm::vec3 npos = direction * speed * time;
        if (colition(room,npos))
            direction = changeDirection();
    }
}

glm::vec3 Golem::changeDirection() {
    glm::vec3 dir;
    dir[0] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    dir[1] = 0;
    dir[2] = std::uniform_real_distribution<float>(-1,1 )(random_engine);
    return glm::normalize(dir);
}

bool Golem::colition(Room *room, glm::vec3 npos) {
    RoomWhere where = room->where(npos[0], npos[2], radio);
    if (where == CAN_BE) {
        position[0] = npos[0];
        position[2] = npos[2];
        return false;
    }
    return true;
}

const float Golem::radio = 1.5f;
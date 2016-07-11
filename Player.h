#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include <GL/glew.h>
#include <GL/glut.h>

#include "Room.h"

using namespace std;

class Player {
public:
    Player();
    ~Player();

    glm::vec3 moveTest(float time);
    glm::vec3 move(RoomWhere where);
    void specialDown(int key);
    void specialUp(int key);
    static GLfloat ambient[4];
    static GLfloat diffuse[4];

    void reset();
    glm::vec3 position() const;

    int getlifePoints() {
        return lifePoints;
    }

    int getAngle() {
        return angle;
    }

    void reciveImpact(int);
    glm::vec3 direction();
    int getPower();
    void upgrade(int item);

    static const float radius;
private:
    float x, z;
    float nx, nz;
    int mv_x, mv_z, angle;
    int power, defense, goldenKey, silverKey, lifePoints;
    float speed;
    int topDown;
    int leftRight;
    float graceTime;
    glm::vec3 dir;
};


#endif //VIDEOGAME_GAMESTATE_H

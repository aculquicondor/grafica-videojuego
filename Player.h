#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include <GL/glut.h>

#include "Model.h"
#include "Room.h"

class Player {
public:
    Player();
    ~Player();

    glm::vec3 moveTest(float time);
    glm::vec3 move(float time, RoomWhere where);
    void draw();
    void specialDown(int key);
    void specialUp(int key);

    void reset();
    glm::vec3 position() const;

    static const float radius;
private:
    static const float speed;

    int live_points;
    float x, z;
    int mv_x, mv_z, angle;

    int topDown;
    int leftRight;

    Model *model;
};


#endif //VIDEOGAME_GAMESTATE_H

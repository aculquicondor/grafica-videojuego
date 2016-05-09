#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include <GL/glut.h>

#include "Model.h"
#include "Room.h"

class Player {
public:
    Player();
    ~Player();

    RoomWhere move(float time, const Room *room);
    void draw();
    void specialDown(int key);
    void specialUp(int key);

private:
    static const float speed;
    static const float radius;

    int live_points;
    float x, z;
    int mv_x, mv_z, angle;

    int topDown;
    int leftRight;

    Model *model;
};


#endif //VIDEOGAME_GAMESTATE_H

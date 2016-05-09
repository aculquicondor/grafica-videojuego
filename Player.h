#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include <GL/glut.h>

#include "Model.h"

class Player {
public:
    Player();
    ~Player();

    void draw(float time);
    void specialDown(int key);
    void specialUp(int key);

private:
    int live_points;
    float x, z;
    float mv_x, mv_z;
    static const float speed;

    int topDown;
    int leftRight;

    Model *model;
};


#endif //VIDEOGAME_GAMESTATE_H

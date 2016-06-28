#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "Model.h"
#include "Room.h"


class Player {
public:
    Player();
    ~Player();

    glm::vec3 moveTest(float time);
    glm::vec3 move(RoomWhere where);
    void draw();
    void specialDown(int key);
    void specialUp(int key);

    void reset();
    glm::vec3 position() const;

    bool attack();

    int livePoints() {
        return live_points;
    }

    static const float radius;
private:
    static const float speed;

    int live_points;
    float x, z;
    float nx, nz;
    int mv_x, mv_z, angle;

    int topDown;
    int leftRight;

    Model *model;

    static GLfloat ambient[4];
    static GLfloat diffuse[4];
};


#endif //VIDEOGAME_GAMESTATE_H

#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H

#include <cmath>

#include <GL/glut.h>
#include <glm/vec3.hpp>

enum RoomWhere {
    CANT_BE,
    CAN_BE,
    N_DOOR,
    E_DOOR,
    S_DOOR,
    W_DOOR,
};

class Room {
public:
    Room();
    ~Room();
    GLint *textures;

    void setDoor(int id, bool value = true);
    bool getDoor(int id);

    RoomWhere where(float x, float z, float radius) const;

    void draw();

    static const float width;

    void discover() {
        _seen = true;
    }

    bool seen() const {
        return _seen;
    }

private:
    bool _seen;
    bool doors[];

    void drawHexahedron(glm::vec3,glm::vec3);

    static const float doorWidth;
};


#endif //VIDEOGAME_ROOM_H

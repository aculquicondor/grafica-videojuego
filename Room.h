#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H

#include <cmath>
#include <list>
#include <random>

#include <GL/glut.h>
#include <glm/vec3.hpp>

#include "RoomWhere.h"
#include "Raticate.h"
#include "Golem.h"

class Room {
public:
    Room();
    ~Room();
    GLint *textures;

    void setDoor(int id, bool value = true);
    bool getDoor(int id);

    RoomWhere where(float x, float z, float radius, Enemy *enemy = nullptr) const;

    void draw();

    static const float width;

    void discover() {
        _seen = true;
    }

    void update(float time, glm::vec3 player_pos, float player_radius);

    bool seen() const {
        return _seen;
    }

private:
    std::list<Enemy *> enemies;
    std::default_random_engine random_engine;

    bool _seen;
    bool doors[];

    void drawHexahedron(glm::vec3,glm::vec3);

    static const float doorWidth;
};


#endif //VIDEOGAME_ROOM_H

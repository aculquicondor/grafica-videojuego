#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H

#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include <glm/vec3.hpp>

#include "RoomWhere.h"
#include "Raticate.h"
#include "Golem.h"
#include "Arbok.h"


class Room {
public:
    Room(GLuint texture);
    ~Room();

    static const float width;

    void setDoor(int id, bool value = true);
    bool getDoor(int id);
    RoomWhere where(float x, float z, float radius, Enemy *enemy = nullptr) const;
    void update(float time, glm::vec3 player_pos, float player_radius);

    void discover() {
        _seen = true;
    }

    bool seen() const {
        return _seen;
    }

    Enemy * getEnemy(int i){
        return enemies[i];
    }

    int enemiesSize(){
        return enemies.size();
    }

private:
    GLuint texture;
    std::vector<Enemy *> enemies;
    std::default_random_engine random_engine;

    bool _seen;
    bool doors[];

    static const float doorWidth;

    static GLfloat ambient[4];
    static GLfloat diffuse[4];
};


#endif //VIDEOGAME_ROOM_H

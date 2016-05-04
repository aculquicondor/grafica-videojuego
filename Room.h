#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H
#include <iostream>
#include <GL/glut.h>
#include "glm/vec3.hpp"


using namespace std;
class Room {
public:
    Room();
    Room(const bool doors[4]);
    ~Room();
    GLint *textures;
    //void setEnemies(int number);

    void draw();
private:
    bool doors[];
    void drawHexahedron(glm::vec3,glm::vec3);

};


#endif //VIDEOGAME_ROOM_H

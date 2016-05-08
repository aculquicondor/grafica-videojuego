#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H

#include <GL/glut.h>
#include <glm/vec3.hpp>


class Room {
public:
    Room();
    ~Room();
    GLint *textures;

    void setDoor(int id, bool value = true);
    bool getDoor(int id);

    void draw();
private:
    bool doors[];
    void drawHexahedron(glm::vec3,glm::vec3);

};


#endif //VIDEOGAME_ROOM_H

#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H
#include <iostream>
#include <GL/glut.h>


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

};


#endif //VIDEOGAME_ROOM_H

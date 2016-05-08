#ifndef VIDEOGAME_GAME_H
#define VIDEOGAME_GAME_H

#include <GL/glut.h>

#include "Map.h"


class Game {
public:
    Game(int &argc, char **argv);

    void mainLoop();

    void reshape(GLsizei width, GLsizei height);

    void key(unsigned char key, int x, int y);

    void newGame();

private:
    void initGL();

    bool mapShow;

    GLsizei width, height;

    Map *map;
};


#endif //VIDEOGAME_GAME_H

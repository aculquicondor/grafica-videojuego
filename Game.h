#ifndef VIDEOGAME_GAME_H
#define VIDEOGAME_GAME_H

#include <cmath>

#include <GL/glut.h>

#include "Map.h"
#include "Player.h"


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
    Player *player;
};


#endif //VIDEOGAME_GAME_H

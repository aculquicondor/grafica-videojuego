#ifndef VIDEOGAME_GAME_H
#define VIDEOGAME_GAME_H

#include <cmath>
#include <chrono>

#include <GL/glut.h>

#include "Map.h"
#include "Player.h"


class Game {
public:
    Game(int &argc, char **argv);

    void mainLoop();

    void reshape(GLsizei width, GLsizei height);

    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);

    void specialDown(int key, int x, int y);
    void specialUp(int key, int x, int y);

    void newGame();

private:
    void initGL();

    bool mapShow;

    GLsizei width, height;

    int row, col;
    float graceTime;

    Map *map;
    Player *player;
    std::chrono::time_point<std::chrono::system_clock> prev_time, new_time;
};


#endif //VIDEOGAME_GAME_H

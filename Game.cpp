#include "Game.h"


Game::Game(int &argc, char **argv) :
        width(1000), height(700), mapShow(false), map(new Map(10, 6)) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Maze");

    initGL();
}


void Game::newGame() {
    delete map;
    map = new Map(10, 6);
}


void Game::initGL() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

void Game::mainLoop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    /* Draw room */

    if (mapShow) {
        glLoadIdentity();
        glViewport(width - 400, 0, 400, 400);
        glOrtho(0, 17, 0, 17, -1, 1);
        map->show();
    }

    glutSwapBuffers();
    glFlush();
}

void Game::reshape(GLsizei width, GLsizei height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void Game::key(unsigned char key, int x, int y) {
    if (key == 'm') {
        mapShow = not mapShow;
    } else if (key == 'r') {
        newGame();
    }
}

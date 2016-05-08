#include <iostream>

#include "Game.h"

using namespace std;

Game *game;


int main(int argc, char *argv[]) {
    game = new Game(argc, argv);

    glutDisplayFunc([]() {
        game->mainLoop();
    });
    glutReshapeFunc([](GLsizei w, GLsizei h) {
        game->reshape(w, h);
    });
    glutKeyboardFunc([](unsigned char c, int x, int y) {
        game->key(c, x, y);
    });

    glutIdleFunc([]() {
        glutPostRedisplay();
    });

    glutMainLoop();

    return 1;
}
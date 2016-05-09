#include <iostream>

#include "Game.h"

using namespace std;

Game *game;


int main(int argc, char *argv[]) {
    game = new Game(argc, argv);

    glutIgnoreKeyRepeat(1);
    glutDisplayFunc([]() {
        game->mainLoop();
    });
    glutReshapeFunc([](GLsizei w, GLsizei h) {
        game->reshape(w, h);
    });
    glutKeyboardFunc([](unsigned char c, int x, int y) {
        game->keyDown(c, x, y);
    });
    glutKeyboardUpFunc([](unsigned char c, int x, int y) {
        game->keyUp(c, x, y);
    });
    glutSpecialFunc([](int c, int x, int y) {
        game->specialDown(c, x, y);
    });
    glutSpecialUpFunc([](int c, int x, int y) {
        game->specialUp(c, x, y);
    });

    glutIdleFunc([]() {
        glutPostRedisplay();
    });

    glutMainLoop();

    return 1;
}
#include "Game.h"


Game::Game(int &argc, char **argv) :
        width(1000), height(700), mapShow(false),
        map(new Map(5, 7)), player(new Player) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Maze");

    initGL();
    prev_time = std::chrono::system_clock::now();

    row = map->startRow();
    col = map->startCol();
}


void Game::newGame() {
    delete map;
    map = new Map(5, 7);
    row = map->startRow();
    col = map->startCol();
}


void Game::initGL() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glLoadIdentity();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::mainLoop() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    new_time = std::chrono::system_clock::now();
    float delta_time = (std::chrono::duration<float>(new_time - prev_time).count());

    glViewport(0, 0, width, height);
    gluPerspective(60, (double) width / height, 1, 100);
    gluLookAt(0, 25, 25, 0, 0, 0, 0, 1, 0);

    Room *room = map->room(row, col);

    RoomWhere where = player->move(delta_time, room);
    if (where > CAN_BE) {
        row += Map::dr[where - 2];
        col += Map::dc[where - 2];
        room = map->room(row, col);
    }

    room->draw();
    player->draw();

    if (mapShow) {
        glLoadIdentity();
        glViewport(width - 400, 0, 400, 400);
        glOrtho(0, 17, 0, 17, -1, 1);
        map->draw(room);
    }

    glutSwapBuffers();
    glFlush();

    prev_time = new_time;
}

void Game::reshape(GLsizei width, GLsizei height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void Game::keyDown(unsigned char key, int x, int y) {
    if (key == 'm') {
        mapShow = not mapShow;
    } else if (key == 'r') {
        newGame();
    }
}


void Game::keyUp(unsigned char key, int x, int y) {
}


void Game::specialDown(int key, int x, int y) {
    player->specialDown(key);
}


void Game::specialUp(int key, int x, int y) {
    player->specialUp(key);
}

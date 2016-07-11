#include "Game.h"


const GLfloat Game::LightAmbient[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
const GLfloat Game::LightDiffuse[4] = { 1.f, 1.f, 1.f, 1.f};
const GLfloat Game::LightDirection[4]= {-5, 10, 2, 0};


Game::Game(int &argc, char **argv) :
        width(1000), height(700), mapShow(false),
        graceTime(0), shot(0),shotTime(0) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Maze");

    initGL();
    prev_time = std::chrono::system_clock::now();

    map = new Map(5, 7);
    player = new Player();
    painter = new Drawable(player);
    painter->setMap(map);
    row = map->startRow();
    col = map->startCol();
}


void Game::newGame() {
    delete painter;
    delete map;
    map = new Map(5, 7);
    row = map->startRow();
    col = map->startCol();
    player->reset();
    painter = new Drawable(player);
    painter->setMap(map);
    shot = 0;
    shotTime = 0;
}


void Game::initGL() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glLoadIdentity();

    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambientGround[4] = {0.3,0.3,0.3,1};
    GLfloat diffuseGround[4] = {0.5,0.5,0.5,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambientGround);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseGround);
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
    painter->setRoom(room);

    glm::vec3 player_pos = player->moveTest(delta_time);
    RoomWhere where = room->where(player_pos.x, player_pos.z, Player::radius);

    if (where > CAN_BE) {
        row += Map::dr[where - N_DOOR];
        col += Map::dc[where - N_DOOR];
        room = map->serCurrent(row, col);
        painter->setRoom(room);
    }

    player_pos = player->move(where);
    shotTime -= delta_time;
    if (shotTime < 0)
        shotTime = 0;
    if (shot) {
        room->createBullet(player->position(), player->direction(), shot, player->getPower(), player->radius);
        shot = 0;
    }
    int impact = room->playerCollision(player->position(),player->radius);
    if (impact > 0){
        player->reciveImpact(impact);
        room->removeDead();
    }

    /*comer items*/
    int item = room->itemCollition(player_pos,player->radius);
    while(item >= 0){
        player->upgrade(item);
        item = room->itemCollition(player_pos,player->radius);
    }
    if (treasureKey){

        treasureKey = false;
    }

    /*siguiente posicion de los enemigos, como tbm la colicion con las balas*/
    room->update(delta_time, player_pos);

    if (player->getlifePoints() <= 0){
        newGame();
        room = map->room(row, col);
        painter->setRoom(room);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, LightDirection);

    painter->draw();


    if (mapShow) {
        glLoadIdentity();
        glViewport(width - 400, 0, 400, 400);
        glOrtho(0, 17, 0, 17, -1, 1);
        painter->drawMiniMap();
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
    } else if (key == 'a'){ //disparo normal con rebote
        if (shotTime <=0){
            shot = 1;
            shotTime = 0.4;
        }
    } else if (key == 's'){ //disparo rapido
        if (shotTime <=0) {
            shot = 2;
            shotTime = 0.4;
        }
    } else if (key == 'd'){ //disparo doble
        if (shotTime <=0) {
            shot = 3;
            shotTime = 0.4;
        }
    } else if (key == 'f'){ //disparo doble
        treasureKey = true;
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

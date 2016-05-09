#include "Room.h"


Room::Room() : _seen(false), random_engine(std::random_device()()) {
    for (int i = 0; i < 4; ++i)
        this->doors[i] = 0;

    int num_enemies = std::uniform_int_distribution<int>(0, 4)(random_engine);
    for (int i = 0; i < num_enemies; ++i) {
        float x = std::uniform_real_distribution<float>(-width, width)(random_engine),
              z = std::uniform_real_distribution<float>(-width, width)(random_engine);
        enemies.push_back(new Raticate(glm::vec3(x, 0, z)));
    }
}


Room::~Room() {
}


void Room::setDoor(int id, bool value) {
    doors[id] = value;
}


bool Room::getDoor(int id) {
    return doors[id];
}

RoomWhere Room::where(float x, float z, float radius) const {
    if (x + radius > Room::width) {
        if (doors[1] and abs(z) < doorWidth)
            return E_DOOR;
        return CANT_BE;
    } if (x - radius < -Room::width) {
        if (doors[3] and abs(z) < doorWidth)
            return W_DOOR;
        return CANT_BE;
    } if (z + radius > Room::width) {
        if (doors[2] and abs(x) < doorWidth)
            return S_DOOR;
        return CANT_BE;
    } if (z - radius < -Room::width) {
        if (doors[0] and abs(x) < doorWidth)
            return N_DOOR;
        return CANT_BE;
    }
    return CAN_BE;
}

void Room::update(float time, glm::vec3 player_pos, float player_radius) {
    for (Enemy *enemy : enemies)
        enemy->step(time, player_pos);
}

void Room::draw(){

    float unit = 1.0;
    float side= 15.0f*unit;

    glBegin(GL_QUADS);
    //ground
    glColor3f(.8,.8,.8);
    glVertex3f(-side,0,side);
    glVertex3f(side,0,side);
    glVertex3f(side,0,-side);
    glVertex3f(-side,0,-side);
    glEnd();

    // north wall
    if (doors[0]) {
        drawHexahedron(glm::vec3(-side-unit,0,-side),glm::vec3(-unit,3*unit,-side-unit));
        drawHexahedron(glm::vec3(unit,0,-side),glm::vec3(side+unit,3*unit,-side-unit));
        drawHexahedron(glm::vec3(-2*unit,0,-side-unit),glm::vec3(-unit,3*unit,-side-3*unit));
        drawHexahedron(glm::vec3(unit,0,-side-unit),glm::vec3(2*unit,3*unit,-side-3*unit));
    }else
        drawHexahedron(glm::vec3(-side-unit,0,-side),glm::vec3(side+unit,3*unit,-side-unit));

    // east wall
    if (doors[1]){
        drawHexahedron(glm::vec3(side,0,side),glm::vec3(side+unit,3*unit,unit));
        drawHexahedron(glm::vec3(side,0,-unit),glm::vec3(side+unit,3*unit,-side));
        drawHexahedron(glm::vec3(side+unit,0,-2*unit),glm::vec3(side+3*unit,3*unit,-unit));
        drawHexahedron(glm::vec3(side+unit,0,unit),glm::vec3(side+3*unit,3*unit,2*unit));
    }else
        drawHexahedron(glm::vec3(side,0,side),glm::vec3(side+unit,3*unit,-side));

    // south wall
    if (doors[2]){
        drawHexahedron(glm::vec3(-side-unit,0,side+unit),glm::vec3(-unit,3*unit,side));
        drawHexahedron(glm::vec3(unit,0,side),glm::vec3(side+unit,3*unit,side+unit));
        drawHexahedron(glm::vec3(-2*unit,0,side+unit),glm::vec3(-unit,3*unit,side+3*unit));
        drawHexahedron(glm::vec3(unit,0,side+unit),glm::vec3(2*unit,3*unit,side+3*unit));
    } else
        drawHexahedron(glm::vec3(-side-unit,0,side+unit),glm::vec3(side+unit,3*unit,side));

    // west wall
    if (doors[3]){
        drawHexahedron(glm::vec3(-side-unit,0,side),glm::vec3(-side,3*unit,unit));
        drawHexahedron(glm::vec3(-side-unit,0,-unit),glm::vec3(-side,3*unit,-side));
        drawHexahedron(glm::vec3(-side-unit,0,2*unit),glm::vec3(-side-3*unit,3*unit,unit));
        drawHexahedron(glm::vec3(-side-unit,0,-unit),glm::vec3(-side-3*unit,3*unit,-2*unit));
    }else
        drawHexahedron(glm::vec3(-side-unit,0,side),glm::vec3(-side,3*unit,-side));

    for (Enemy *enemy : enemies)
        enemy->draw();
}

void Room::drawHexahedron(glm::vec3 lower,glm::vec3 upper) {
    glBegin(GL_QUADS);
    // front side
    glColor3f(.6,.6,.6);
    glVertex3f(lower[0],lower[1],lower[2]);
    glVertex3f(upper[0],lower[1],lower[2]);
    glVertex3f(upper[0],upper[1],lower[2]);
    glVertex3f(lower[0],upper[1],lower[2]);
    // back side
    glVertex3f(lower[0],lower[1],upper[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(upper[0],lower[1],upper[2]);
    // down side
    glColor3f(.4,.4,.4);
    glVertex3f(lower[0],lower[1],upper[2]);
    glVertex3f(upper[0],lower[1],upper[2]);
    glVertex3f(upper[0],lower[1],lower[2]);
    glVertex3f(lower[0],lower[1],lower[2]);
    // up side
    glVertex3f(lower[0],upper[1],lower[2]);
    glVertex3f(upper[0],upper[1],lower[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    // left side
    glColor3f(.5,.5,.5);
    glVertex3f(lower[0],lower[1],upper[2]);
    glVertex3f(lower[0],lower[1],lower[2]);
    glVertex3f(lower[0],upper[1],lower[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    // right side
    glVertex3f(upper[0],lower[1],lower[2]);
    glVertex3f(upper[0],lower[1],upper[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(upper[0],upper[1],lower[2]);

    glEnd();
}

const float Room::width = 15;

const float Room::doorWidth = .8f;

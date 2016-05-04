#include "Room.h"


Room::Room() {
    for (int i = 0; i < 4; ++i)
        doors[i] = false;
}


Room::Room(const bool doors[4]) {
    for (int i = 0; i < 4; ++i)
        this->doors[i] = doors[i];
}


Room::~Room() {
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
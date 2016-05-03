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

    // north wall
    if (doors[0]) {
        glColor3f(1, 1, 1);
        glVertex3f(-unit, 0, -side); //door
        glVertex3f(unit, 0, -side);
        glVertex3f(unit, 3*unit, -side);
        glVertex3f(-unit, 3*unit, -side);
    }
    else {
        glColor3f(.6, .6, .6);
        glVertex3f(-unit, 0, -side); //door
        glVertex3f(unit, 0, -side);
        glVertex3f(unit, 3*unit, -side);
        glVertex3f(-unit, 3*unit, -side);
    }
    glColor3f(.6,.6,.6);
    glVertex3f(unit,0,-side); //  right wall
    glVertex3f(side,0,-side);
    glVertex3f(side,3*unit,-side);
    glVertex3f(unit,3*unit,-side);
    glVertex3f(-side,0,-side); //  left wall
    glVertex3f(-unit,0,-side);
    glVertex3f(-unit,3*unit,-side);
    glVertex3f(-side,3*unit,-side);
    glVertex3f(-side,3*unit,-side); //  upper wall
    glVertex3f(side,3*unit,-side);
    glVertex3f(side,8*unit,-side);
    glVertex3f(-side,8*unit,-side);

    // east wall
    if (doors[1]) {
        glColor3f(1, 1, 1);
        glVertex3f(side, 0, -unit); //door
        glVertex3f(side, 0, unit);
        glVertex3f(side, 3*unit, unit);
        glVertex3f(side, 3*unit, -unit);
    }
    else {
        glColor3f(.6, .6, .6);
        glVertex3f(side, 0, -unit); //door
        glVertex3f(side, 0, unit);
        glVertex3f(side, 3*unit, unit);
        glVertex3f(side, 3*unit, -unit);
    }
    glColor3f(.6,.6,.6);
    glVertex3f(side,0,unit); //  rigth wall
    glVertex3f(side,0,side);
    glVertex3f(side,3*unit,side);
    glVertex3f(side,3*unit,unit);
    glVertex3f(side,0,-side); //  left wall
    glVertex3f(side,0,-unit);
    glVertex3f(side,3*unit,-unit);
    glVertex3f(side,3*unit,-side);
    glVertex3f(side,3*unit,-side); //  upper wall
    glVertex3f(side,3*unit,side);
    glVertex3f(side,8*unit,side);
    glVertex3f(side,8*unit,-side);

    // south wall
    if (doors[2]){
        glColor3f(1,1,1);
        glVertex3f(unit,0,side);
        glVertex3f(-unit,0,side);
        glVertex3f(-unit,3*unit,side);
        glVertex3f(unit,3*unit,side);
    }
    else{
        glColor3f(.6,.6,.6);
        glVertex3f(unit,0,side);
        glVertex3f(-unit,0,side);
        glVertex3f(-unit,3*unit,side);
        glVertex3f(unit,3*unit,side);
    }
    glColor3f(.6,.6,.6);
    glVertex3f(-unit,0,side); //  right wall
    glVertex3f(-side,0,side);
    glVertex3f(-side,3*unit,side);
    glVertex3f(-unit,3*unit,side);
    glVertex3f(side,0,side); //  left wall
    glVertex3f(unit,0,side);
    glVertex3f(unit,3*unit,side);
    glVertex3f(side,3*unit,side);
    glVertex3f(side,3*unit,side); //  upper wall
    glVertex3f(-side,3*unit,side);
    glVertex3f(-side,8*unit,side);
    glVertex3f(side,8*unit,side);

    // west wall
    if (doors[3]){
        glColor3f(1,1,1);
        glVertex3f(-side,0,unit);
        glVertex3f(-side,0,-unit);
        glVertex3f(-side,3*unit,-unit);
        glVertex3f(-side,3*unit,unit);
    }
    else{
        glColor3f(.6,.6,.6);
        glVertex3f(-side,0,unit);
        glVertex3f(-side,0,-unit);
        glVertex3f(-side,3*unit,-unit);
        glVertex3f(-side,3*unit,unit);
    }
    glColor3f(.6,.6,.6);
    glVertex3f(-side,0,-unit); //  rigth wall
    glVertex3f(-side,0,-side);
    glVertex3f(-side,3*unit,-side);
    glVertex3f(-side,3*unit,-unit);
    glVertex3f(-side,0,side); //  left wall
    glVertex3f(-side,0,unit);
    glVertex3f(-side,3*unit,unit);
    glVertex3f(-side,3*unit,side);
    glVertex3f(-side,3*unit,side); //  rigth wall
    glVertex3f(-side,3*unit,-side);
    glVertex3f(-side,8*unit,-side);
    glVertex3f(-side,8*unit,side);

    glEnd();
}


//
// Created by jasillo on 28/06/16.
//

#include "Drawable.h"

Drawable::Drawable(Player * p): myPlayer(p) {
    // por ahora solo se dibuja una room a la vez
    myRoom = nullptr;
    myModels.push_back(Model::getModel("pikachu"));
    myModels.push_back(Model::getModel("raticate"));
    myModels.push_back(Model::getModel("golem"));
    myModels.push_back(Model::getModel("arbok"));
    myModels.push_back(Model::getModel("chest"));
}

Drawable::~Drawable() {
    myParticles = nullptr;
    myMap = nullptr;
    myPlayer = nullptr;
    myRoom = nullptr;
    //for (Model *m : myModels)
        //delete m;
    myModels.clear();
}

void Drawable::setMap(Map * m) {
    myMap = m;
}

void Drawable::setRoom(Room * r) {
    myRoom = r;
    myParticles = r->getParticles();
}

void Drawable::draw() {
    glEnable(GL_COLOR_MATERIAL);
    GLfloat ambientGround[4] = {0.3,0.3,0.3,1};
    GLfloat diffuseGround[4] = {0.5,0.5,0.5,1};
    glMaterialfv(GL_FRONT,GL_AMBIENT,ambientGround);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseGround);

    drawRoom(myRoom);

    int enemysize = myRoom->enemiesSize();
    for (int i=0 ; i<enemysize ; ++i)
        drawEnemies(myRoom->getEnemy(i));

    int itemsize = myRoom->itemsSize();
    for (int i=0 ; i<itemsize ; ++i)
        drawItem(myRoom->getItem(i));

    for (ParticleEngine *pe : *myParticles)
        drawParticles(pe);

    drawPlayer();
}


void Drawable::drawString(GLfloat x, GLfloat y, const std::string &s) {
    glRasterPos2f(x, y);
    for (char c: s)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void Drawable::drawInfo(GLsizei width, GLsizei height) {
    glLoadIdentity();
    glViewport(0, 0, width, height);
    float in_width = 30;
    glOrtho(0, in_width, 0, in_width * height / width, -1, 1);
    glColor3f(0.2, 0.2, 0.9);
    int life = myPlayer->getlifePoints() / 10;
    drawString(0, 0.2, "Life:");
    glPushMatrix();
    glTranslatef(3, 0.5, 0);
    for (int i = 0; i < life; ++i) {
        glutSolidSphere(0.5, 10, 10);
        glTranslatef(1, 0, 0);
    }
    glPopMatrix();
    glColor3f(0.2, 0.9, 0.2);
    drawString(0, 1.2, "Power:");
    glTranslatef(3, 1.5, 0);
    int power = myPlayer->getPower() / 10;
    for (int i = 0; i < power; ++i) {
        glutSolidSphere(0.5, 10, 10);
        glTranslatef(1, 0, 0);
    }
}


/* --- --------------------------------------------------------------*/
void Drawable::drawMiniMap(GLsizei width) {
    glLoadIdentity();
    glViewport(width - 400, 0, 400, 400);
    glOrtho(0, 17, 0, 17, -1, 1);
    float x,y;
    float rows = myMap->getRows();
    float cols = myMap->getColumns();

    float unit = 16.0f / std::max(rows, cols);
    float initialX = .5f;
    float initialY = unit * rows + .5f;

    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(unit * cols + 1, 0);
    glVertex2f(unit * cols + 1, unit * rows + 1);
    glVertex2f(0, unit * rows + 1);
    glEnd();

    Room* room;
    for (int r=0 ; r<rows; ++r){
        for (int c=0 ; c<cols ; ++c) {
            room = myMap->room(r,c);
            if (room and room->seen()) {
                x = initialX + c * unit + unit*0.5f;
                y = initialY - r * unit - unit*0.5f;
                if (room == myMap->getCurrentRoom())
                    glColor3f(.3f, .3f, .6f);
                else
                    glColor3f(1.0, .5f, 0.0f);
                //dibujar habitaciones
                drawSquare(glm::vec2(x-unit*0.45,y-unit*0.45),glm::vec2(x+unit*0.45,y+unit*0.45));
                //dibujar pasadizos
                if (room->getDoor(0)) //north
                    drawSquare(glm::vec2(x-0.1*unit , y+.45*unit),glm::vec2(x+0.1*unit , y+0.5*unit));
                if (room->getDoor(1)) //east
                    drawSquare(glm::vec2(x+.45*unit , y-0.1*unit),glm::vec2(x+.5*unit , y+0.1*unit));
                if (room->getDoor(2)) //south
                    drawSquare(glm::vec2(x-0.1*unit , y-0.5*unit),glm::vec2(x+.1*unit, y-.45*unit));
                if (room->getDoor(3)) //west
                    drawSquare(glm::vec2(x-0.5*unit , y-.1*unit),glm::vec2(x-.45*unit, y+.1*unit));
            }
        }
    }
}

void Drawable::drawSquare(glm::vec2 min, glm::vec2 max) {
    glBegin(GL_QUADS);
        glVertex2f(min[0],min[1]);
        glVertex2f(max[0],min[1]);
        glVertex2f(max[0],max[1]);
        glVertex2f(min[0],max[1]);
    glEnd();
}

/* --- --------------------------------------------------------------*/

void Drawable::drawRoom(Room * r) {
    float unit = 1.0;
    float side= 15.0f*unit;

    //ground
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glColor3f(.45,.45, .45);
    glVertex3f(-side,0,side);
    glVertex3f(side,0,side);
    glVertex3f(side,0,-side);
    glVertex3f(-side,0,-side);
    glEnd();

    // north wall
    if (r->getDoor(0)) {
        drawHexahedron(glm::vec3(-side-unit,0,-side),glm::vec3(-unit,3*unit,-side-unit));
        drawHexahedron(glm::vec3(unit,0,-side),glm::vec3(side+unit,3*unit,-side-unit));
        drawHexahedron(glm::vec3(-2*unit,0,-side-unit),glm::vec3(-unit,3*unit,-side-3*unit));
        drawHexahedron(glm::vec3(unit,0,-side-unit),glm::vec3(2*unit,3*unit,-side-3*unit));
    }else
        drawHexahedron(glm::vec3(-side-unit,0,-side),glm::vec3(side+unit,3*unit,-side-unit));

    // east wall
    if (r->getDoor(1)){
        drawHexahedron(glm::vec3(side,0,side),glm::vec3(side+unit,3*unit,unit));
        drawHexahedron(glm::vec3(side,0,-unit),glm::vec3(side+unit,3*unit,-side));
        drawHexahedron(glm::vec3(side+unit,0,-unit),glm::vec3(side+3*unit,3*unit,-2*unit));
        drawHexahedron(glm::vec3(side+unit,0,2*unit),glm::vec3(side+3*unit,3*unit,unit));
    }else
        drawHexahedron(glm::vec3(side,0,side),glm::vec3(side+unit,3*unit,-side));

    // south wall
    if (r->getDoor(2)){
        drawHexahedron(glm::vec3(-side-unit,0,side+unit),glm::vec3(-unit,3*unit,side));
        drawHexahedron(glm::vec3(unit,0,side+unit),glm::vec3(side+unit,3*unit,side));
        drawHexahedron(glm::vec3(-2*unit,0,side+3*unit),glm::vec3(-unit,3*unit,side+unit));
        drawHexahedron(glm::vec3(unit,0,side+3*unit),glm::vec3(2*unit,3*unit,side+unit));
    } else
        drawHexahedron(glm::vec3(-side-unit,0,side+unit),glm::vec3(side+unit,3*unit,side));

    // west wall
    if (r->getDoor(3)){
        drawHexahedron(glm::vec3(-side-unit,0,side),glm::vec3(-side,3*unit,unit));
        drawHexahedron(glm::vec3(-side-unit,0,-unit),glm::vec3(-side,3*unit,-side));
        drawHexahedron(glm::vec3(-side-unit,0,2*unit),glm::vec3(-side-3*unit,3*unit,unit));
        drawHexahedron(glm::vec3(-side-unit,0,-unit),glm::vec3(-side-3*unit,3*unit,-2*unit));
    }else
        drawHexahedron(glm::vec3(-side-unit,0,side),glm::vec3(-side,3*unit,-side));
}

void Drawable::drawHexahedron(glm::vec3 lower,glm::vec3 upper) {

    glColor3f(.4,.4,.4);
    glBegin(GL_QUADS);
    // front side
    glNormal3f(0,0,1);
    glVertex3f(lower[0],lower[1],lower[2]);
    glVertex3f(upper[0],lower[1],lower[2]);
    glVertex3f(upper[0],upper[1],lower[2]);
    glVertex3f(lower[0],upper[1],lower[2]);
    // back side
    glNormal3f(0,0,-1);
    glVertex3f(lower[0],lower[1],upper[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(upper[0],lower[1],upper[2]);
    // up side
    glNormal3f(0,1,0);
    glVertex3f(lower[0],upper[1],lower[2]);
    glVertex3f(upper[0],upper[1],lower[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    // left side
    glNormal3f(1,0,0);
    glVertex3f(lower[0],lower[1],upper[2]);
    glVertex3f(lower[0],lower[1],lower[2]);
    glVertex3f(lower[0],upper[1],lower[2]);
    glVertex3f(lower[0],upper[1],upper[2]);
    // right side
    glNormal3f(-1,0,0);
    glVertex3f(upper[0],lower[1],lower[2]);
    glVertex3f(upper[0],lower[1],upper[2]);
    glVertex3f(upper[0],upper[1],upper[2]);
    glVertex3f(upper[0],upper[1],lower[2]);

    glEnd();
}

/* --- --------------------------------------------------------------*/

void Drawable::drawEnemies(Enemy * e) {
    glm::vec3 pos = e->position();
    float angle = e->getAngle();
    glPushMatrix();
    glTranslatef(pos.x, 0, pos.z);
    glEnable(GL_COLOR_MATERIAL);
    if (e->type() == 1){
        glColor3f(0.7f, 0.7f, 0.2f);
        glMaterialfv(GL_FRONT,GL_AMBIENT, Raticate::ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE, Raticate::diffuse);
        glScalef(.35f, .35f, .35f);
        glRotatef(angle * 57.2957f, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        myModels[1]->draw();
    }else if (e->type() == 2){
        glColor3f(.5f, .55f, .35f);
        glMaterialfv(GL_FRONT,GL_AMBIENT, Golem::ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE, Golem::diffuse);
        glScalef(.25f, .25f, .25f);
        glRotatef(angle * 57.2957f, 0, 1, 0);
        myModels[2]->draw();
    }else if (e->type() == 3){
        glColor3f(0.45f, 0.1f, 0.5f);
        glMaterialfv(GL_FRONT,GL_AMBIENT, Arbok::ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE, Arbok::diffuse);
        glScalef(0.25f, 0.25f, 0.25f);
        glRotatef(angle * 57.2957f, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        myModels[3]->draw();
    }else if (e->type() == 4){ // balas
        glColor3f(0.45f, 0.1f, 0.5f);
        glTranslatef(0,1,0);
        glutSolidSphere(e->radius(),10,10);
        //std::cout<< pos.x<<" "<<pos.z<<std::endl;
    } else if (e->type() == 5){ // cofre
        glColor3f(0.357, 0.267, 0.169);
        glTranslatef(0,1,0);
        myModels[4]->draw();
    }

    glPopMatrix();
}

void Drawable::drawPlayer() {
    glm::vec3 pos = myPlayer->position();
    int angle = myPlayer->getAngle();
    glPushMatrix();
    glTranslated(pos.x, 0, pos.z);
    glRotated(angle, 0, 1, 0);
    glScalef(.05f, .05f, .05f);
    glColor3f(0.9f, 0.9f, 0);
    glMaterialfv(GL_FRONT,GL_AMBIENT, Player::ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, Player::diffuse);
    myModels[0]->draw();
    glPopMatrix();
}

void Drawable::drawItem(Item * i) {
    glm::vec3 pos = i->position();
    glColor3f(1, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(pos.x,1,pos.z);
    glutSolidSphere(Item::radio,10,10);
    glPopMatrix();
}

bool compareParticles(Particle* particle1, Particle* particle2) {
    return particle1->pos.z < particle2->pos.z;
}

void Drawable::drawParticles(ParticleEngine *pe) {
        //glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, textureId);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        sort(pe->myParticles.begin(), pe->myParticles.end(), compareParticles);
        glBegin(GL_QUADS);
        for (Particle *p : pe->myParticles){
            if (p->alive)
            {
                glm::vec3 pos = p->pos;
                glColor4f(1,p->alpha,0,p->alpha);
                float s = p->size;
                glTexCoord2f(0,0);
                glVertex3f(pos.x - s, pos.y - s, pos.z);
                glTexCoord2f(0,1);
                glVertex3f(pos.x - s, pos.y + s, pos.z);
                glTexCoord2f(1,1);
                glVertex3f(pos.x + s, pos.y + s, pos.z);
                glTexCoord2f(1,0);
                glVertex3f(pos.x + s, pos.y - s, pos.z);
            }
        }
        glEnd();
}
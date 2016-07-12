//
// Created by jasillo on 28/06/16.
//

#ifndef VIDEOGAME_DRAWABLE_H
#define VIDEOGAME_DRAWABLE_H

#include <vector>
#include "TextureManager.h"
#include <GL/glut.h>

#include "Map.h"
#include "Room.h"
#include "Player.h"
#include "Raticate.h"
#include "Golem.h"
#include "Arbok.h"
#include "Item.h"
#include "ParticleEngine.h"
#include "Model.h"

class Drawable {
private:
    Map * myMap;
    Room * myRoom;
    vector<Model *> myModels;
    Player * myPlayer;
    //vector<Item *> myItems;

    void drawString(GLfloat x, GLfloat y, const std::string &s);
    void drawSquare(glm::vec2 min, glm::vec2 max);
    void drawHexahedron(glm::vec3 lower,glm::vec3 upper);
    void drawRoom(Room *);
    void drawEnemies(Enemy *);
    void drawPlayer();
    void drawItem(Item *);
    vector<ParticleEngine *> * myParticles;
    void drawParticles(ParticleEngine *pe);
public:
    Drawable(Player *);
    ~Drawable();


    void setMap(Map *);
    void setRoom(Room *);
    void draw();
    void drawMiniMap(GLsizei width);
    void drawInfo(GLsizei width, GLsizei height);
};


#endif //VIDEOGAME_DRAWABLE_H

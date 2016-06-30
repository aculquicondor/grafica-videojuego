//
// Created by jasillo on 28/06/16.
//

#ifndef VIDEOGAME_DRAWABLE_H
#define VIDEOGAME_DRAWABLE_H

#include "Map.h"
#include "Room.h"
#include "Player.h"
#include "Raticate.h"
#include "Golem.h"
#include "Arbok.h"
//#include "Item.h"
#include <GL/glut.h>
#include <vector>
#include "TextureManager.h"
#include "Model.h"

class Drawable {
private:
    Map * myMap;
    vector<Room *> myRooms;
    vector<Enemy *> myEnemys;
    vector<Model *> myModels;
    Player * myPlayer;
    //vector<Item *> myItems;

    void drawSquare(glm::vec2 min, glm::vec2 max);
    void drawHexahedron(glm::vec3 lower,glm::vec3 upper);
    void drawRoom(Room *);
    void drawEnemies(Enemy *);
    void drawPlayer();
public:
    Drawable(Player *);
    ~Drawable();

    void scan();
    void setMap(Map *);
    void draw();
    void drawMiniMap();
    void drawPlayeStatus();
    void drawMonsterStatus();
};


#endif //VIDEOGAME_DRAWABLE_H

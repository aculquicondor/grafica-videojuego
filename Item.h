//
// Created by jasillo on 08/05/16.
//
#include "glm/vec3.hpp"
#include <GL/glut.h>

#ifndef VIDEOGAME_ITEM_H
#define VIDEOGAME_ITEM_H
#define GOLDEN_KEY 0
#define SILVER_KEY 1
#define LIFE 2
#define SPEED 3
#define POWER 4
#define TRUNK 5
#define SIZE 1

using namespace std;

class Item {
public:
    Item(int);
    Item(glm::vec3, int);
    ~Item();
    void setPosition(glm::vec3);
    void draw();
    bool* getUpgrade();
private:
    glm::vec3 center;
    Item * myItems[6];
    bool upgrade[6];
    void drawKey();
    void drawHeart();
    void drawShoe();
    void drawLightning();
    void drawTrunk();
    void generateItemTrunk();
};


#endif //VIDEOGAME_ITEM_H

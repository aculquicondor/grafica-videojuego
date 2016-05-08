//
// Created by jasillo on 08/05/16.
//
#ifndef VIDEOGAME_ITEM_H
#define VIDEOGAME_ITEM_H

#include "glm/vec3.hpp"
#include <GL/glut.h>


struct ItemType {
    GOLDEN_KEY;
    SILVER_KEY;
    LIFE;
    SPEED;
    POWER;
    TRUNK;
};


class Item {
public:
    Item(ItemType itemType);
    Item(glm::vec3 pos, ItemType itemType);
    ~Item();
    void setPosition(glm::vec3 pos);
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

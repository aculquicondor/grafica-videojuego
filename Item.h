//
// Created by jasillo on 08/05/16.
//
#ifndef VIDEOGAME_ITEM_H
#define VIDEOGAME_ITEM_H

#include <vector>

#include "glm/vec3.hpp"
#include <GL/glut.h>

class Item {
public:
    Item(int);
    Item(glm::vec3 , int);
    ~Item();
    static const float radio;
    void setPosition(glm::vec3 pos);
    bool addItem(Item *);
    Item* getItem();
    int getType();

private:
    glm::vec3 cPosition;
    /*0=power, 1=defense, 2=speed, 3=lifepoints, 4=silverkey, 5=goldenkey 6=trunk*/
    int type;
    //si es un cofre tiene items almacenados
    std::vector<Item *> myItems;
};


#endif //VIDEOGAME_ITEM_H

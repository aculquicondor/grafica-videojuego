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
    ~Item();
    static const float radio;
    void setPosition(glm::vec3 pos);
    int getType();

    glm::vec3 position() const {
        return cPosition;
    }

private:
    glm::vec3 cPosition;
    /*0=power, 1=defense, 2=speed, 3=lifepoints, 4=silverkey, 5=goldenkey*/
    int type;
    //si es un cofre tiene items almacenados
};


#endif //VIDEOGAME_ITEM_H

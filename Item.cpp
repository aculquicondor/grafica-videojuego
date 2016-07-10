//
// Created by jasillo on 08/05/16.
//

#include "Item.h"

Item::Item(int i): type(i){

}

Item::~Item() {

}

void Item::setPosition(glm::vec3 pos) {
    cPosition = pos;
}

int Item::getType() {
    return type;
}

const float Item::radio = 0.5f;
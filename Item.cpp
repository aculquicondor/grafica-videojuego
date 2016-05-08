//
// Created by jasillo on 08/05/16.
//

#include "Item.h"

Item::Item(int itemType): center(glm::vec3(0,0,0)) {

    for (int i=0; i<6 ; ++i) {
        upgrade[i] = false;
        myItems[i] = nullptr;
    }
    upgrade[itemType] = true;
    if (itemType == TRUNK)
        generateItemTrunk();
}

Item::Item(glm::vec3 pos, int itemType) : center(pos){

    for (int i=0; i<6 ; ++i){
        upgrade[i] = false;
        myItems[i] = nullptr;
    }
    upgrade[itemType] = true;
    if (itemType == TRUNK)
        generateItemTrunk();
}

Item::~Item() {

}

void Item::setPosition(glm::vec3 pos) {
    center = pos;
}

bool* Item::getUpgrade() {
    return upgrade;
}

void Item::draw(){
    if (upgrade[0]){
        glColor3f(1,0.6,0.1); //gold
        drawKey();
    }else if (upgrade[1]){
        glColor3f(0.8,0.8,0.8);
        drawKey();
    }else if (upgrade[2]){
        glColor3f(1,0,0);
        drawHeart();
    }else if (upgrade[3]){
        glColor3f(0.8,0.8,1);
        drawShoe();
    }else if (upgrade[4]){
        glColor3f(1,1,0);
        drawLightning();
    }else if (upgrade[5]){
        glColor3f(0.4,0.2,0.3);
        drawTrunk();
    }
}

void Item::drawKey() {

}

void Item::drawHeart() {

}

void Item::drawLightning() {

}

void Item::drawShoe() {

}

void Item::drawTrunk() {

}
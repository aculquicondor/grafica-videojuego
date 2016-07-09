//
// Created by jasillo on 08/05/16.
//

#include "Item.h"

Item::Item(int i): type(i){

}


Item::Item(glm::vec3 pos, int itemType) :
                            cPosition(pos),
                            type(itemType){

}

Item::~Item() {
    for(Item* i : myItems)
        delete i;
}

void Item::setPosition(glm::vec3 pos) {
    cPosition = pos;
}

bool Item::addItem(Item *i) {
    if (type==6){
        myItems.push_back(i);
        return true;
    }
    return false;
}

Item* Item::getItem() {
    if (myItems.empty())
        return nullptr;
    Item *i = myItems.back();
    myItems.pop_back();
    return i;
}

int Item::getType() {
    return type;
}

const float Item::radio = 0.5f;
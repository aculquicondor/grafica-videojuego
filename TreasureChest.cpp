//
// Created by jasillo on 09/07/16.
//

#include "TreasureChest.h"
TreasureChest::TreasureChest(glm::vec3 pos):
                            cPosition(pos),
                            lifePoints(1){

}

TreasureChest::~TreasureChest() {
    for (Item* i : myItems)
        delete i;
    myItems.clear();
}

glm::vec3 TreasureChest::position() const {
    return cPosition;
}

glm::vec3 TreasureChest::stepTest(float time, glm::vec3 playerPosition) {
    return cPosition;
}

float TreasureChest::getAngle() {
    return angle;
}

int TreasureChest::type() {
    return 5;
}

int TreasureChest::getLifePoints() {
    return lifePoints;
}

int TreasureChest::getPower() {
    return 1;
}

void TreasureChest::createItem(int typeItem) {
    myItems.push_back(new Item(typeItem));
}

Item* TreasureChest::getItem() {
    if (myItems.empty())
        return nullptr;
    Item* i = myItems.back();
    myItems.pop_back();
    return i;
}

void TreasureChest::receiveImpact(int) {
    lifePoints = 0;
}

const float TreasureChest::radio = 0.9f;
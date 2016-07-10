//
// Created by jasillo on 09/07/16.
//

#include "TreasureChest.h"
TreasureChest::TreasureChest(glm::vec3 pos):cPosition(pos) {

}

TreasureChest::~TreasureChest() {

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

const float TreasureChest::radio = 0.5f;
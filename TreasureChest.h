//
// Created by jasillo on 09/07/16.
//

#ifndef VIDEOGAME_TREASURECHEST_H
#define VIDEOGAME_TREASURECHEST_H

#include <vector>
#include <glm/vec3.hpp>
#include "Enemy.h"
#include "Item.h"

class TreasureChest: public Enemy {
public:
    TreasureChest(glm::vec3 pos);
    ~TreasureChest();

    glm::vec3 stepTest(float time, glm::vec3 playerPosition);
    void step() {};
    static const float radio;
    float radius() const {
        return radio;
    }
    glm::vec3 position() const;
    void reflectDirection(float,float) {};
    float getAngle();
    int type();
    int getLifePoints();
    int getPower();
    void receiveImpact(int);
    void createItem(int typeItem);
    Item* getItem();

private:
    glm::vec3 cPosition;
    float angle;
    int lifePoints;
    std::vector<Item*> myItems;
};


#endif //VIDEOGAME_TREASURECHEST_H

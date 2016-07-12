#define GLM_FORCE_RADIANS
#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H

#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "RoomWhere.h"
#include "Raticate.h"
#include "Golem.h"
#include "Arbok.h"
#include "Bullet.h"
#include "TreasureChest.h"
#include "Item.h"


class Room {
public:
    Room(GLuint texture);
    ~Room();

    static const float width;

    void setDoor(int id, bool value = true);
    bool getDoor(int id);
    RoomWhere where(float x, float z, float radius) const;
    int playerCollision(glm::vec3, float);
    bool enemiesCollision(Enemy*, glm::vec3);
    int bulletCollision(Enemy*);
    void update(float time, glm::vec3 player_pos);

    void discover() {
        _seen = true;
    }

    bool seen() const {
        return _seen;
    }

    Enemy * getEnemy(int i){
        return enemies[i];
    }
    Item * getItem(int i){
        return items[i];
    }

    int enemiesSize(){
        return enemies.size();
    }
    int itemsSize(){
        return items.size();
    }

    void createBullet(glm::vec3, glm::vec3, int, int, float);
    void removeDead();
    void generateEnemies(int,bool);
    void generateItems(int key);
    void generateTreasureChest();
    int itemCollition(glm::vec3 pos, float r);
    bool openTreasure(glm::vec3 pos,glm::vec3 dir, float r);
    vector<ParticleEngine *> * getParticles();

private:
    GLuint texture;
    std::vector<Enemy *> enemies;
    std::vector<Item *> items;
    std::vector<ParticleEngine *> particles;
    std::default_random_engine random_engine;

    bool _seen;
    bool doors[];
    static const float doorWidth;
    static GLfloat ambient[4];
    static GLfloat diffuse[4];

    glm::vec3 generatePosition(float);
    bool collition(glm::vec3 pos1, glm::vec3 pos2, float r1, float r2) const ;
    void getEnemyItems(Enemy *e);
};


#endif //VIDEOGAME_ROOM_H

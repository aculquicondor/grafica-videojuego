#ifndef VIDEOGAME_MAP_H
#define VIDEOGAME_MAP_H

#include <random>
#include <vector>

#include <glm/vec2.hpp>

#include "Room.h"


using namespace std;

class Map {
public:
    Map(int rows, int cols);
    virtual ~Map();
    int getRows() const;
    int getColumns() const;

    int startRow() const {
        return start_r;
    }
    int startCol() const {
        return start_c;
    }
    int exitRow() const {
        return exit_r;
    }
    int exitCol() const {
        return exit_c;
    }

    Room *room(int r, int c) {
        return map[r][c];
    }

    Room * getCurrentRoom(){
        return currentRoom;
    }

    Room * serCurrent(int r, int c);

    static const int dr[], dc[];

private:
    Room ***map;
    int rows, cols;
    int start_r, start_c;
    int exit_r, exit_c;
    std::default_random_engine random_engine;
    GLuint room_texture;
    Room * currentRoom;
    vector<Room *> myRooms; //el primer elemento es el estar y el ultimo es exit
    vector<int> generateRandomList(int min, int max, int iter);

    bool valid(int r, int c);
    void dfs(int r, int c, int dir, double prob);
};


#endif //VIDEOGAME_MAP_H

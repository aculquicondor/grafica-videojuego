#ifndef VIDEOGAME_MAP_H
#define VIDEOGAME_MAP_H

#include <random>
#include <iostream>

#include "Room.h"


class Map {
public:
    Map(int rows, int cols);
    virtual ~Map();
    int getRows() const;
    int getColumns() const;
    void show() const;

private:
    Room ***map;
    int rows, cols;
    int start_r, start_c;
    int exit_r, exit_c;
    std::default_random_engine random_engine;

    bool valid(int r, int c);
    void dfs(int r, int c, int dir, bool first = false);
    static const int dr[], dc[];
};


#endif //VIDEOGAME_MAP_H

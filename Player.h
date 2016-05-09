#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "Model.h"

class Player {
public:
    Player();
    ~Player();

    void draw() const;

private:
    int live_points;
    int room_row, room_col;

    Model *model;
};


#endif //VIDEOGAME_GAMESTATE_H

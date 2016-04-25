#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H


class Player {
public:
    Player();
    virtual ~Player();
private:
    int live_points;
    int room_row, room_col;
};


#endif //VIDEOGAME_GAMESTATE_H

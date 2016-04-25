#ifndef VIDEOGAME_ROOM_H
#define VIDEOGAME_ROOM_H


class Room {
public:
    Room(bool doors[4]);
    ~Room();
    void setEnemies(int number);
private:
    bool doors[];
};


#endif //VIDEOGAME_ROOM_H

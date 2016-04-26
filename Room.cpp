#include "Room.h"


Room::Room() {
    for (int i = 0; i < 4; ++i)
        doors[i] = false;
}


Room::Room(const bool doors[4]) {
    for (int i = 0; i < 4; ++i)
        this->doors[i] = doors[i];
}


Room::~Room() {
}

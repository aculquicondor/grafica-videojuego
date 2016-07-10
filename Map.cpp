#include "Map.h"


Map::Map(int rows, int cols) : rows(rows), cols(cols),
                               random_engine(std::random_device()()) {
    map = new Room**[rows];
    map[0] = new Room*[rows * cols];
    for (int i = 1; i < rows; ++i)
        map[i] = map[i - 1] + cols;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            map[i][j] = nullptr;

    start_r = std::uniform_int_distribution<int>(0, rows - 1)(random_engine);
    start_c = std::uniform_int_distribution<int>(0, cols - 1)(random_engine);
    dfs(start_r, start_c, 0, 1);
    map[start_r][start_c]->discover();
    currentRoom = map[start_r][start_c];

    /*generar enemigos*/
    for (int i=1 ; i<myRooms.size()-1 ; ++i)
        myRooms[i]->generateEnemies(0, false);
    myRooms.back()->generateEnemies(0, true); //boss
    /*generar items en los enemigos*/
    for (int i=1 ; i<myRooms.size() ; ++i)
        myRooms[i]->generateItems(0);
    /*generar llaves*/
    for (int i=0 ; i< 6; ++i){ // llaves plateadas
        int ran = std::uniform_int_distribution<int>(1, myRooms.size()-1)(random_engine);
        myRooms[ran]->generateItems(2);
    }
    int ran = std::uniform_int_distribution<int>(1, myRooms.size()-1)(random_engine);
    myRooms[ran]->generateItems(1); // llave dorada
    /* generar cofres*/
    for (int i=0 ; i<4 ; ++i){// 4 cofres
        ran = std::uniform_int_distribution<int>(1, myRooms.size()-1)(random_engine);
        myRooms[ran]->generateTreasureChest();
    }
}


Map::~Map() {
    myRooms.clear();
    currentRoom = nullptr;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (map[i][j])
                delete map[i][j];
    delete[] map[0];
    delete[] map;
}


bool Map::valid(int r, int c) {
    return r >= 0 and r < rows and c >= 0 and c < cols;
}


void Map::dfs(int r, int c, int dir, double prob) {
    exit_r = r;
    exit_c = c;
    int nr, nc;
    map[r][c] = new Room(room_texture);
    myRooms.push_back(map[r][c]);
    for (int i = 0; i < 4; ++i) {
        int j = (dir + i) % 4;
        nr = r + dr[j];
        nc = c + dc[j];
        if (valid(nr, nc) and
                std::uniform_real_distribution<double>()(random_engine) <
                        (((dir ^ j) & 1) ? prob * .5 : prob)) {
            if (map[nr][nc] == nullptr)
                dfs(nr, nc, j, prob * .9);
            map[r][c]->setDoor(j);
            map[nr][nc]->setDoor((j + 2) % 4);
        }
    }
}

int Map::getRows() const {
    return rows;
}

int Map::getColumns() const {
    return cols;
}

const int Map::dr[] = {-1, 0, 1, 0};

const int Map::dc[] = {0, 1, 0, -1};

Room* Map::serCurrent(int r, int c) {
    currentRoom = map[r][c];
    currentRoom->discover();
    return currentRoom;
}

vector<int> Map::generateRandomList(int min, int max, int iter) {
    vector<int> list(max-min,0);
    for (int i=0 ; i<list.size() ; ++i)
        list[i] = i+min;
    for (int i=0 ; i<iter ;++i){
        int ran = std::uniform_int_distribution<int>(i, list.size()-1)(random_engine);
        swap(list[i],list[ran]);
    }
    return list;
}
#include "Map.h"


Map::Map(int rows, int cols) : rows(rows), cols(cols),
                               random_engine((unsigned int)time(0)) {
    map = new Room**[rows];
    map[0] = new Room*[rows * cols];
    for (int i = 1; i < rows; ++i)
        map[i] = map[i - 1] + cols;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            map[i][j] = nullptr;

    start_r = std::uniform_int_distribution<int>(0, rows)(random_engine);
    start_c = std::uniform_int_distribution<int>(0, cols)(random_engine);
    dfs(start_r, start_c, 0);
}


Map::~Map() {
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


void Map::dfs(int r, int c, int dir) {
    exit_r = r;
    exit_c = c;
    int nr, nc;
    map[r][c] = new Room();
    for (int i = 0; i < 4; ++i) {
        int j = (dir + i) % 4;
        nr = r + dr[j];
        nc = c + dc[j];
        if (valid(nr, nc) and
                std::uniform_real_distribution<double>()(random_engine) < (((dir ^ j) & 1) ? .05 : .75)) {
            if (map[nr][nc] == nullptr)
                dfs(nr, nc, j);
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

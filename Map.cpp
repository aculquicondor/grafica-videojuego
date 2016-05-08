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
                std::uniform_real_distribution<double>()(random_engine) < (((dir ^ j) & 1) ? .25 : .75)) {
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


void Map::show()
{
    float x,y;
    //posicion inicial superior izquierda
    float initialX = -8.0f;
    float initialY = 8.0f;
    //lado de cada cuadrante
    float unit = 16.0f/ (cols>rows?cols:rows);

    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-8.5f,-8.5f);
    glVertex2f(8.5f,-8.5f);
    glVertex2f(8.5,8.5);
    glVertex2f(-8.5f,8.5);
    glEnd();

    Room* room;
    for (int r=0 ; r<rows; ++r){
        for (int c=0 ; c<cols ; ++c) {
            if (map[r][c]) {
                x = initialX + r * unit + unit*0.5f;
                y = initialY - c * unit - unit*0.5f;
                glColor3f(1.0, .5f, 0.0f);
                room = map[r][c];
                //dibujar habitaciones
                drawSquare(glm::vec2(x-unit*0.45,y-unit*0.45),glm::vec2(x+unit*0.45,y+unit*0.45));
                //dibujar pasadizos
                if (room->getDoor(3)) //north
                    drawSquare(glm::vec2(x-0.1*unit , y+.45*unit),glm::vec2(x+0.1*unit , y+0.5*unit));
                if (room->getDoor(2)) //east
                    drawSquare(glm::vec2(x+.45*unit , y-0.1*unit),glm::vec2(x+.5*unit , y+0.1*unit));
                if (room->getDoor(1)) //south
                    drawSquare(glm::vec2(x-0.1*unit , y-0.5*unit),glm::vec2(x+.1*unit, y-.45*unit));
                if (room->getDoor(0)) //west
                    drawSquare(glm::vec2(x-0.5*unit , y-.1*unit),glm::vec2(x-.45*unit, y+.1*unit));
                //cout<<r<<" "<<c<<" "<<room<<endl;
            }
        }
    }
}

void Map::drawSquare(glm::vec2 min, glm::vec2 max){
    glBegin(GL_QUADS);
    glVertex2f(min[0],min[1]);
    glVertex2f(max[0],min[1]);
    glVertex2f(max[0],max[1]);
    glVertex2f(min[0],max[1]);
    glEnd();
}
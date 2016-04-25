#ifndef VIDEOGAME_MAP_H
#define VIDEOGAME_MAP_H


class Map {
public:
    Map(int rows, int cols);
    virtual ~Map();
private:
    int **map;
    int start_x, start_y;
    int exit_x, exit_y;
    int getRows() const;
    int getColumns() const;
};


#endif //VIDEOGAME_MAP_H

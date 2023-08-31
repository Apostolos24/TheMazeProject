#ifndef THEMAZEPROJECT_MAZE_H
#define THEMAZEPROJECT_MAZE_H

#include <iostream>

class Maze
{
private:
    int rows;
    int cols;
    int** matrix;

    int start_x;
    int start_y;
    int end_x;
    int end_y;

    bool valid_direction(int x, int y, int direction);

public:
    Maze (int _rows, int _cols);

    // getters
    int get_rows();
    int get_cols();
    int get_start_x();
    int get_start_y();
    int get_end_x();
    int get_end_y();
    int get_total_tiles();
    //

    void generate_random();

    friend std::ostream& operator<< (std::ostream& out,Maze& maze);

    void print();

    };

#endif //THEMAZEPROJECT_MAZE_H

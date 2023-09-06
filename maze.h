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

    bool valid_direction(int x, int y, int direction)  const;

public:
    Maze (int _rows, int _cols);

    // getters
    int get_rows() const;
    int get_cols() const;
    int get_start_x() const;
    int get_start_y() const;
    int get_end_x() const;
    int get_end_y() const;
    int get_total_tiles() const;
    //

    void generate_random();

    friend std::ostream& operator<< (std::ostream& out,Maze& maze);

    };

#endif //THEMAZEPROJECT_MAZE_H

//
// Created by agtfs on 29/8/2023.
//

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

    bool valid_correct_path(int x, int y, int direction);

    bool valid_path_start(int x, int y);

public:
    Maze (int _rows, int _cols);

    void generate_random();

    friend std::ostream& operator<< (std::ostream& out,Maze& maze);

    };

#endif //THEMAZEPROJECT_MAZE_H

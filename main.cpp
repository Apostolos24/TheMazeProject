#include <iostream>
#include "maze.h"

int main() {
    Maze MyMaze(54,84);
    MyMaze.generate_random();
    std::cout << MyMaze;
    }

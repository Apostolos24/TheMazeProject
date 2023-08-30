#include <iostream>
#include "maze.h"

int main() {
    Maze MyMaze(23, 52);
    MyMaze.generate_random();
    std::cout << MyMaze;
}

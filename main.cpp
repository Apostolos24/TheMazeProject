#include <iostream>
#include "maze.h"

int main() {
    Maze MyMaze(20,32);
    MyMaze.generate_random();
    std::cout << MyMaze;
}

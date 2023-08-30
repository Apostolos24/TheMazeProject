#include "maze.h"

    bool Maze::valid_correct_path(int x, int y, int direction) {
        switch(direction) {
            case 0:
                if(y > 1 && x != 0 && x != cols - 1 && !(x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y-1] == 1) && !(x+1 < cols - 1 && matrix[x+1][y] == 1 || matrix[x+1][y-1] == 1)) return true;
                else return false;

            case 1:
                if(y < rows - 2 && x != 0 && x != cols - 1 && !(x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y+1] == 1) && !(x+1 < cols -1 && matrix[x+1][y] == 1 || matrix[x+1][y+1] == 1)) return true;
                else return false;

            case 2:
                if(x < cols - 2 && y != 0 && y != rows - 1 && !(y-1 > 0 && matrix[x][y-1] == 1 && matrix[x+1][y-1] == 1) && !(y+1 < rows - 1 && matrix[x][y+1] == 1 && matrix[x+1][y+1] == 1)) return true;
                else return false;

            case 3:
                if(x > 1 && y != 0 && y != rows - 1 && !(y-1 > 0 && matrix[x][y-1] == 1 && matrix[x-1][y-1] == 1) && !(y+1 < cols - 1 && matrix[x][y+1] == 1 && matrix[x-1][y+1] == 1)) return true;
                else return false;

            default:
                return false;

        }

    }

    
    bool Maze::valid_path_start(int x, int y) {
        if(matrix[x][y] == 1 &&
           ((x+1 < cols - 1 && matrix[x+1][y] == 0) || (x-1 > 0 && matrix[x-1][y] == 0) || (y+1 < rows - 1 && matrix[x][y+1] == 0) || (y-1 > 0 && matrix[x][y-1] == 0)) //at least one direction has a wall that can be turned into a new path
                ) return true;
        else return false;
    }

    
    Maze::Maze (int _rows, int _cols): rows(_rows), cols(_cols), start_x(-1), start_y(-1), end_x(-1), end_y(-1) {
        //creating a 2D matrix
        matrix = new int*[cols];
        for(int i=0; i < cols; ++i) matrix[i] = new int[rows];

        for(int i=0; i < cols; ++i) { //initializing the matrix to be empty
            for(int j=0; j < rows; ++j) {
                matrix[i][j] = 0;
            }
        }

    }


    void Maze::generate_random() {
        srand(time(0));

        //generating a random exit located at the border of the maze
        if(rand()%2 == 0) {
            end_x = rand()%cols;
            std::cout<< end_x << std::endl;

            if(end_x == 0 || end_x == cols-1) end_y = rand()%(rows-2) + 1;
            else end_y = rand()%2 * (rows-1);
            std::cout<< end_y << std::endl;
        }
        else {
            end_y = rand()%rows;
            std::cout<< end_y << std::endl;

            if(end_y == 0 || end_y == rows-1) end_x = rand()%(cols-2) + 1;
            else end_x = rand()%2 * (cols-1);
            std::cout<< end_x << std::endl;
        }
        std::cout << end_x << " " << end_y << std::endl << std::endl;
        matrix[end_x][end_y] = 1; //endpoint


        //generating the correct path
        int length = rand()%((rows-3)*(cols-3)/2);
        int move; //0:up 1:down 2:right 3:left
        int last_move = rand()%4;
        int x = end_x;
        int y = end_y;

        while(length > 0) {
            //picks a direction at random and then cycles through the direction until it finds a valid direction it can move to
            move = rand()%5;
            if(move==4) move = last_move; //straighter paths, 40% chance of continuing on the same direction
            while(!valid_correct_path(x, y, move)) move = (++move)%4;

            switch(move) {
                case 0: //up
                    matrix[x][--y] = 1;
                    break;

                case 1: //down
                    matrix[x][++y] = 1;
                    break;

                case 2: //right
                    matrix[++x][y] = 1;
                    break;

                case 3: //left
                    matrix[--x][y] = 1;
                    break;

            }
            --length;
            last_move = move;

        }
        start_x = x;
        start_y = y;


        //generating random paths
        int total_path_tiles = rand()%((rows-2)*(cols-2)/2); // the total numbers of tiles available for new paths

        while(total_path_tiles > 0) {
            int path_tiles = rand()%((rows-3)*(cols-3)/2); // the number of tiles the currently generated path will have
            total_path_tiles -= path_tiles;

            //random start from an existing path
            x=1;
            y=1;
            bool legal_start = false;
            while(!legal_start) {
                int iteration_length = rand()%((rows-1)*(cols-1));

                while(iteration_length > 0) {
                    for(int i = 1; i < cols-1; ++i) {
                        for(int j = 1; j < rows-1; ++j) {
                            if(valid_path_start(i,j)) {
                                x=i;
                                y=j;
                                legal_start = true;
                            }

                            if(--iteration_length == 0) { // if iteration_length == 0 then break out of the while loop
                                i = cols - 1;
                                break;
                            }

                        }
                    }


                }
            }


            //move  0:down 1:up 2:right 3:left
            last_move = rand()%4;

            while(path_tiles > 0) {
                move = rand()%5;
                if(move==4) move = last_move; //straighter paths

                switch(move) {
                    case 0:
                        //if(matrix[x][y+1] == 1) break; //old path
                        if(y > rows - 3 || x == 0 || x == cols - 1) break; //out of bounds
                        if((x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y+1] == 1) || (x+1 < cols -1 && matrix[x+1][y] == 1 || matrix[x+1][y+1] == 1)) break; //path formation
                        matrix[x][++y] = 1;
                        --path_tiles;
                        break;

                    case 1:
                        //if(matrix[x][y-1] == 1) break; //old path
                        if(y < 2 || x == 0 || x == cols - 1) break;
                        if((x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y-1] == 1) || (x+1 < cols - 1 && matrix[x+1][y] == 1 || matrix[x+1][y-1] == 1)) break;
                        matrix[x][--y] = 1;
                        --path_tiles;
                        break;

                    case 2:
                        //if(matrix[x+1][y] == 1) break; //old path
                        if(x > cols - 3 || y == 0 || y == rows - 1) break;
                        if((y-1 > 0 && matrix[x][y-1] == 1 && matrix[x+1][y-1] == 1) || (y+1 < rows - 1 && matrix[x][y+1] == 1 && matrix[x+1][y+1] == 1)) break;
                        matrix[++x][y] = 1;
                        --path_tiles;
                        break;

                    case 3:
                        //if(matrix[x-1][y] == 1) break; //old path
                        if(x < 2 || y == 0 || y == rows - 1) break;
                        if((y-1 > 0 && matrix[x][y-1] == 1 && matrix[x-1][y-1] == 1) || (y+1 < cols - 1 && matrix[x][y+1] == 1 && matrix[x-1][y+1] == 1)) break;
                        matrix[--x][y] = 1;
                        --path_tiles;
                        break;

                }
                last_move = move;

            }




        }



        matrix[start_x][start_y] = 2; //start point
        matrix[end_x][end_y] = 3; // endpoint
    }


    std::ostream& operator<< (std::ostream& out,Maze& maze) {
        for(int j=0; j < maze.rows; ++j) {
            for(int i=0; i < maze.cols; ++i) {
                if(maze.matrix[i][j] == 0) out << "# ";
                else if(maze.matrix[i][j] == 1) out << "  ";
                else if(maze.matrix[i][j] == 2) out << "s ";
                else if(maze.matrix[i][j] == 3) out << "g ";
                else out << "? ";
            }
            out << '\n';
        }

        return out;
    }

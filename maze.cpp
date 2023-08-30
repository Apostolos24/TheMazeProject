#include "maze.h"

    bool Maze::valid_direction(int x, int y, int direction) {
        switch(direction) {
            case 0: // up
                if(y > 1 && x != 0 && x != cols - 1 && !(x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y-1] == 1) && !(x+1 < cols - 1 && matrix[x+1][y] == 1 || matrix[x+1][y-1] == 1)) return true;
                else return false;

            case 1: // down
                if(y < rows - 2 && x != 0 && x != cols - 1 && !(x-1 > 0 && matrix[x-1][y] == 1 && matrix[x-1][y+1] == 1) && !(x+1 < cols -1 && matrix[x+1][y] == 1 || matrix[x+1][y+1] == 1)) return true;
                else return false;

            case 2: // right
                if(x < cols - 2 && y != 0 && y != rows - 1 && !(y-1 > 0 && matrix[x][y-1] == 1 && matrix[x+1][y-1] == 1) && !(y+1 < rows - 1 && matrix[x][y+1] == 1 && matrix[x+1][y+1] == 1)) return true;
                else return false;

            case 3: // left
                if(x > 1 && y != 0 && y != rows - 1 && !(y-1 > 0 && matrix[x][y-1] == 1 && matrix[x-1][y-1] == 1) && !(y+1 < cols - 1 && matrix[x][y+1] == 1 && matrix[x-1][y+1] == 1)) return true;
                else return false;

            default:
                return false;

        }

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
            while(!valid_direction(x, y, move)) move = (++move)%4;

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
            //random start
            x = rand()%(cols-2) + 1;
            y = rand()%(rows-2) + 1;
            int connected = false; //checks if the new path is connected with another path (ensuring that way that *almost* every tile can lead to the exit)

            //move  0:down 1:up 2:right 3:left
            last_move = rand()%4;

            while(!connected) {
                //picks a direction at random and then cycles through the direction until it finds a valid direction it can move to
                move = rand()%5;
                if(move==4) move = last_move; //straighter paths, 40% chance of continuing on the same direction

                int cycles = 1;
                while(!valid_direction(x, y, move) && cycles < 5) {
                    move = (++move)%4;
                    ++cycles;
                }
                if(cycles == 5) break; // if there is no valid direction available we try again with a new path

                switch(move) {
                    case 0: //up
                        if(matrix[x][y-1] == 1) connected = true;
                        else matrix[x][--y] = 1;
                        break;

                    case 1: //down
                        if(matrix[x][y+1] == 1) connected = true;
                        else matrix[x][++y] = 1;
                        break;

                    case 2: //right
                        if(matrix[x+1][y] == 1) connected = true;
                        else matrix[++x][y] = 1;
                        break;

                    case 3: //left
                        if(matrix[x-1][y] == 1) connected = true;
                        else matrix[--x][y] = 1;
                        break;

                }
                --total_path_tiles;
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

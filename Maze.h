// John Leeds
// 3/2/2022
// Maze.h
#include <vector>
#ifndef MAZE_H
#define MAZE_H

void setSeed();
int ranNum(int, int);

class MazeCell{
    public:
        MazeCell();
        
        int getVisitStatus();
        bool getUp();
        bool getRight();
        bool getDown();
        bool getLeft();

        void setVisitStatus(int val);
        void setUp(bool val);
        void setRight(bool val);
        void setDown(bool val);
        void setLeft(bool val);
    private:
        int visitStatus;
        bool up;
        bool right;
        bool down;
        bool left;
};

class Maze{
    public:
        /*
         * Constructor
         * Creates a maze of unvisited MazeCells, all with 4 walls
         */
        Maze(int length, int height);
       
        /*
         * clearVisitStatus
         * Sets the visit status of every maze cell to unvisited (0)
         */
        void clearVisitStatus();

        /*
         * generate
         * Creates a maze with a depth-first search
         */
        void generate(bool print);
        
        /*
         * checkNeighbors
         * Returns true if there is a neighbor that has not been visited
         */
        std::vector<std::vector<int>> checkNeighbors(int x, int y);

        void analyzeCell(int x, int y);
        /*
         * solve
         * Solves the maze
         */
        void solve(bool print);
        std::vector<int> pickMove(int x, int y);
        /*
         * show
         * Prints a visual representation of the maze to the consul
         */
        void show();
    private:
        std::vector<std::vector<MazeCell>> myMaze;
};

#endif

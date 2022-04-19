// John Leeds
// 3/2/2022
// Maze.cpp
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // usleep
#include "Maze.h"
#include "Stack.h"
using namespace std;

void setSeed(){
    srand(time(NULL));
}
/*
 * ranNum
 * Preconditions:
 * Receives a minimum and maximum value (inclusive)
 * defaults to 0-3
 * Returns:
 * A pseudo-random number between min and max (inclusive)
 */
int ranNum(int min = 0, int max = 3){
    return rand()%(min+max+1) + min;
}

MazeCell::MazeCell(){
    visitStatus = 0;
    up = true;
    right = true;
    down = true;
    left = true;
}
// Getters
int MazeCell::getVisitStatus(){
    return visitStatus;
}
bool MazeCell::getUp(){
    return up;
}
bool MazeCell::getRight(){
    return right;
}
bool MazeCell::getDown(){
    return down;
}
bool MazeCell::getLeft(){
    return left;
}
// Setters
void MazeCell::setVisitStatus(int val){
    visitStatus = val;
}
void MazeCell::setUp(bool val){
    up = val;
}
void MazeCell::setRight(bool val){
    right = val;
}
void MazeCell::setDown(bool val){
    down = val;
}
void MazeCell::setLeft(bool val){
    left = val;
}

/*
 * Constructor
 * Creates a maze of unvisited MazeCells, all with 4 walls
 */
Maze::Maze(int length = 8, int height = 8){
    for ( int h = 0; h<height; h++ ){
        vector<MazeCell> newRow;
        myMaze.push_back(newRow);
        for ( int l = 0; l<length; l++ ){
        MazeCell newCell;
        myMaze[h].push_back(newCell);
        }
    }
}

/*
 * clearVisitStatus
 * Sets the visit status of every maze cell to unvisited (0)
 */
void Maze::clearVisitStatus(){
    for (size_t h = 0; h<myMaze.size(); h++ ){
        for ( size_t l = 0; l<myMaze[0].size(); l++ ){
            myMaze[h][l].setVisitStatus(0);
        }
    }
}

/*
 * generate
 * Creates a maze with a depth-first search
 */
void Maze::generate(bool print = false){
    int coords[2] = {0, 0};
    Stack path(coords);
    myMaze[0][0].setVisitStatus(2);
    while ( path.isEmpty() == false ){
        int* curCoords = path.pop();
        vector<vector<int>> valid = checkNeighbors(curCoords[0], curCoords[1]);
        if ( valid.size() != 0 ){
            int coords[2] = {curCoords[0], curCoords[1]};
            path.push(coords);
            int num = ranNum(0, valid.size() - 1);
            vector<int> selection = valid[num];
            int x = selection[0];
            int y = selection[1];
            
            // removing wall
            if ( y<coords[1] ){
                myMaze[coords[1]][coords[0]].setUp(false);
                myMaze[y][x].setDown(false);
            }
            else if ( x>coords[0] ){
                myMaze[coords[1]][coords[0]].setRight(false);
                myMaze[y][x].setLeft(false);
            }
            else if ( y>coords[1] ){
                myMaze[coords[1]][coords[0]].setDown(false);
                myMaze[y][x].setUp(false);
            }
            else if ( x<coords[0] ){
                myMaze[coords[1]][coords[0]].setLeft(false);
                myMaze[y][x].setRight(false);
            }
            myMaze[coords[1]][coords[0]].setVisitStatus(1);
            myMaze[y][x].setVisitStatus(2);
            coords[0] = x;
            coords[1] = y;
            path.push(coords);

        }
        else{
            myMaze[curCoords[1]][curCoords[0]].setVisitStatus(1);
            if ( path.isEmpty() != true ){
                curCoords = path.peek();
                myMaze[curCoords[1]][curCoords[0]].setVisitStatus(2);
            }
        }
        if ( print ){
            usleep(300000);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;    
            show();
        }
    }
    clearVisitStatus();
}

/*
 * checkNeighbors
 * Returns true if there is a neighbor that has not been visited
 */
vector<vector<int>> Maze::checkNeighbors(int x, int y){
    int values[4][2] = {{x, y+1}, {x+1, y}, {x, y-1}, {x-1, y}};
    vector<vector<int>> possibilities; 
    for ( int i = 0; i<4; i++ ){
        x = values[i][0];
        y = values[i][1];
        if ( x >= 0 && x < myMaze[0].size() &&
             y >= 0 && y < myMaze.size()){
            if ( myMaze[y][x].getVisitStatus() == 0){
                vector<int> coords = {x, y};
                possibilities.push_back(coords);

            }
        }
    }
    return possibilities;
}

void Maze::analyzeCell(int x, int y){
    cout << "~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "no walls:";
    if ( myMaze[y][x].getUp() == false ) cout << " Up";
    if ( myMaze[y][x].getRight() == false ) cout << " Right";
    if ( myMaze[y][x].getDown() == false ) cout << " Down";
    if ( myMaze[y][x].getLeft() == false ) cout << " Left";
    cout << "\n~~~~~~~~~~~~~~~~~~~" << endl;
}

/*
 * solve
 * Solves the maze
 */
void Maze::solve(bool print){
    myMaze[0][0].setVisitStatus(2);
    int curCoords[2] = {0, 0};
    Stack path(curCoords);
    int goalX = static_cast<int>(myMaze[0].size() - 1);
    int goalY = static_cast<int>(myMaze.size() - 1);
    int goal[2] = {goalX, goalY};
    while ( curCoords[0] != goal[0] || curCoords[1] != goal[1]){
        vector<int> nextMove = pickMove(curCoords[0], curCoords[1]);
        if ( nextMove[0] == -1 ){ // go back
            myMaze[curCoords[1]][curCoords[0]].setVisitStatus(1);
            int* coordsPtr = path.pop();
            curCoords[0] = coordsPtr[0];
            curCoords[1] = coordsPtr[1];
            myMaze[curCoords[1]][curCoords[0]].setVisitStatus(2);
        }
        else{
            myMaze[curCoords[1]][curCoords[0]].setVisitStatus(1);
            curCoords[0] = nextMove[0];
            curCoords[1] = nextMove[1];
            int coords[2] = {curCoords[0], curCoords[1]};
            path.push(coords);
            myMaze[curCoords[1]][curCoords[0]].setVisitStatus(2);
        }
        if ( print ){
            usleep(300000);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;    
            show();
        }
    }
}

vector<int> Maze::pickMove(int x, int y){
    // pick whether to prioritize moving right or down
    bool rightOrDown = false; // false = right
    vector<vector<int>> possibilities = {{x, y-1}, {x+1, y},
                                         {x, y+1}, {x-1, y}};
    if ( myMaze.size() - y > myMaze[0].size() - x ){
        rightOrDown = true; 
    }
    // whether the program can move right or down
    bool moveRight = false;
    bool moveDown = false;
    if ( x < myMaze[0].size() - 1 && myMaze[y][x].getRight() == false &&
         myMaze[y][x+1].getVisitStatus() == 0 ){
        moveRight = true;
    }
    if ( y < myMaze.size() - 1 && myMaze[y][x].getDown() == false &&
         myMaze[y+1][x].getVisitStatus() == 0 ){
        moveDown = true;
    }
    // return if one of these is true
    if ( moveRight || moveDown ){
        if ( moveRight && rightOrDown == false ){
            return possibilities[1];
        }
        else if ( moveDown && rightOrDown ){
            return possibilities[2];
        }
        else if ( moveRight ){
            return possibilities[1];
        }
        else{
            return possibilities[2];
        } 
    }
    bool moveLeft = false;
    bool moveUp = false;
    if ( x > 0 && myMaze[y][x].getLeft() == false && 
         myMaze[y][x-1].getVisitStatus() == 0 )
        moveLeft = true;
    if ( y > 0 && myMaze[y][x].getUp() == false && 
         myMaze[y-1][x].getVisitStatus() == 0 )
        moveUp = true;
    if ( moveLeft && rightOrDown ){
        return possibilities[3];
    }
    if ( moveUp && rightOrDown == false ){
        return possibilities[0];
    }
    if ( moveLeft ){
        return possibilities[3];
    }
    if ( moveUp ){
        return possibilities[0];
    }
    vector<int> back = {-1, -1};
    return back;


}

/* ‾
 * show
 * Prints a visual representation of the maze to the console
 */
void Maze::show(){
    size_t height = myMaze.size();
    size_t length = myMaze[0].size();
/*    for ( size_t h = 0; h<height; h++ ){
        cout << "(" << 0 << ", " << h << "): " << myMaze[h][0].getLeft() << endl;
        cout << "(" << length-1 << ", " << h << "): " << myMaze[h][length-1].getRight() << endl;
    }
    for ( size_t l = 0; l<length; l++ ){
        cout << "(" << 0 << ", " << l << "): " << myMaze[0][l].getUp() << endl;
        cout << "(" << height-1 << ", " << l << "): " << myMaze[height-1][l].getDown() << endl;
    }
    cout << endl;*/
    for ( size_t h = 0; h<height; h++ ){
        cout << "|";
        for ( size_t l = 0; l<length; l++ ){ // vertical walls
            if ( myMaze[h][l].getUp() ) cout << "-";
            else cout << " ";

            if ( l != length-1 ) cout << '-';
        }
        cout << "|";
        cout << endl;
        for ( size_t l = 0; l<length; l++ ){ // horizontal layer
            if ( myMaze[h][l].getLeft() == false || (h == 0 && l == 0 )) cout << ' ';
            else cout << '|';
            if ( myMaze[h][l].getVisitStatus() == 2 ) cout << '@';
            else if ( myMaze[h][l].getVisitStatus() == 1 ) cout << '#';
            else cout << ' ';
        }
        if ( h == height-1) cout << '$';
        else if ( myMaze[h][length-1].getRight() ) cout << '|';
        cout << endl;
        }
    cout << '|';
    for ( size_t l = 0; l<length; l++ ){ // bottom edge
        if ( l == length-1 ) cout << "-|";
        else cout << "--";
    }
    cout << endl;
}

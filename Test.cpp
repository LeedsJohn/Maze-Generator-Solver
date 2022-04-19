#include <iostream>
#include "Maze.h"
#include "Stack.h"
using namespace std;

void testStack(){
    int coords[2] = {0, 0};
    Stack test(coords);
    cout << "creating stack with value (0, 0)" << endl;
    test.show();
    cout << "Pushing (5, 10) to it" << endl;
    coords[0] = 5;
    coords[1] = 10;
    test.push(coords);
    test.show();
    cout << "Peeking at top value (5, 10)" << endl;
    int* newCoords = test.peek();
    cout << newCoords[0] << " " << newCoords[1] << endl;
    cout << "Popping top value (5, 10)" << endl;
    newCoords = test.pop();
    test.show();
    cout << newCoords[0] << " " << newCoords[1] << endl;
    cout << "Test is empty - false, true" << endl;
    cout << test.isEmpty() << endl;
    test.pop();
    cout << test.isEmpty() << endl;
    cout << "Length: 0, 1, 2, 3" << endl;
    for ( int i = 0; i<4; i++){
        cout << test.length() << endl;
        test.push(coords);
    }
}

int main(){
    testStack();
}

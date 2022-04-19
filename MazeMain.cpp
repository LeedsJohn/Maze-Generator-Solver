#include <iostream>
#include "Maze.h"
using namespace std;

int main(){
    setSeed(); 
    Maze john(16, 8);
    john.generate(false);
    cout << "\n\n" << endl;
    john.show();
    char a;
    cin >> a;
    john.solve(true);
    cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
    john.show();
}

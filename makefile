all: test maze
maze: Maze.o MazeMain.o Stack.o
	g++ Maze.o MazeMain.o Stack.o -o maze
test: Test.o Stack.o Maze.o
	g++ Test.o Stack.o Maze.o -o test

Test.o: Test.cpp Stack.cpp Stack.h Maze.cpp Maze.h
	g++ -c Test.cpp -o Test.o
Maze.o: Maze.cpp Maze.h Stack.cpp Stack.h
	g++ -c Maze.cpp -o Maze.o
Stack.o: Stack.cpp Stack.h
	g++ -c Stack.cpp -o Stack.o

clean:
	rm *.o maze test

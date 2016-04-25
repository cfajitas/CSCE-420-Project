CC = g++-5 -std=c++14
all: Astar

Problem.o: Problem.h Problem.cpp
	$(CC) -c Problem.cpp

Gate.o: Gate.h Gate.cpp
	$(CC) -c Gate.cpp

Circuit.o: Gate.h Circuit.h Circuit.cpp
	$(CC) -c Circuit.cpp

Solver.o: Problem.h Gate.h Circuit.h Solver.h Solver.cpp
	$(CC) -c Solver.cpp

Astar.o: Problem.h Gate.h Circuit.h Solver.h Astar.cpp
	$(CC) -c Astar.cpp
	
Astar: Problem.o Gate.o Circuit.o Solver.o Astar.o
	$(CC) -o Astar Problem.o Gate.o Circuit.o Solver.o Astar.o

clean:
	rm -f *.o Astar
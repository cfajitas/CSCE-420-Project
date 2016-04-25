CC = g++-5 -std=c++14
all: Genetic Astar

Problem.o: Problem.h Problem.cpp
	$(CC) -c Problem.cpp

Gate.o: Gate.h Gate.cpp
	$(CC) -c Gate.cpp

Circuit.o: Gate.h Circuit.h Circuit.cpp
	$(CC) -c Circuit.cpp

Solver.o: Problem.h Gate.h Circuit.h Solver.h Solver.cpp
	$(CC) -c Solver.cpp

Factorize.o: Gate.h Circuit.h Factorize.h Factorize.cpp
	$(CC) -c Factorize.cpp

Genetic.o: Problem.h Gate.h Circuit.h Solver.h Genetic.cpp
	$(CC) -c Genetic.cpp

Astar.o: Problem.h Gate.h Circuit.h Solver.h Astar.cpp
	$(CC) -c Astar.cpp

Genetic: Problem.o Gate.o Circuit.o Solver.o Genetic.o Factorize.o
	$(CC) -o Genetic Problem.o Gate.o Circuit.o Solver.o Genetic.o Factorize.o
	
Astar: Problem.o Gate.o Circuit.o Solver.o Astar.o Factorize.o
	$(CC) -o Astar Problem.o Gate.o Circuit.o Solver.o Astar.o Factorize.o

clean:
	rm -f *.o Genetic Astar
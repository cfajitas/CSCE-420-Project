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

Genetic.o: Problem.h Gate.h Circuit.h Solver.h Factorize.h Genetic.cpp
	$(CC) -c Genetic.cpp

Astar.o: Problem.h Gate.h Circuit.h Solver.h Factorize.h Astar.cpp
	$(CC) -c Astar.cpp

Genetic: Problem.o Gate.o Circuit.o Solver.o Factorize.o Genetic.o 
	$(CC) -o Genetic Problem.o Gate.o Circuit.o Solver.o Factorize.o Genetic.o
	
Astar: Problem.o Gate.o Circuit.o Solver.o Factorize.o Astar.o
	$(CC) -o Astar Problem.o Gate.o Circuit.o Solver.o Factorize.o Astar.o

clean:
	rm -f *.o Genetic Astar
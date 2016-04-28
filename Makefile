CC = g++ -std=c++14
all: Main 

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

Main.o: Problem.h Gate.h Circuit.h Solver.h Factorize.h Main.cpp
	$(CC) -c Main.cpp
	
Main: Problem.o Gate.o Circuit.o Solver.o Factorize.o Main.o
	$(CC) -o Main Problem.o Gate.o Circuit.o Solver.o Factorize.o Main.o

clean:
	rm -f *.o Main

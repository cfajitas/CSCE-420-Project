#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Problem.h"
#include "Circuit.h"

using namespace std;

class Solver
{
private:
    vector<Problem> problems;
    vector<Circuit> circuits;
    vector<int> limits;
    int solutionLoc;
public:
    Solver(int nc);
    void addProblem(Problem p);
    void run();
    void addGates();
    int checkSolution();
    void calcFitness();
    void clean();
    int getSolutionLocation();
    void printSolution(string file);
    void print();
    static bool sortFitness(const Circuit &l, const Circuit &r)
    {
    	return l.getFitness() > r.getFitness();
    }
};
#endif
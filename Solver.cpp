#include "Solver.h"

Solver::Solver()
{
    solution=false;
}

void Solver::addGate(Gate g)
{
    gates.push_back(g);
}

bool Solver::isSolution()
{
    return solution;
}

void Solver::checkSolution(unsigned int a, unsigned int b, unsigned int c)
{
    
}
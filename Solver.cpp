#include "Solver.h"

Solver::Solver()
{
    fitness=0;
}

void Solver::addGate(Gate g)
{
    gates.push_back(g);
}

void Solver::calculateSolution(bitset<16> a, bitset<16> b)
{
    bool flip = false;
    for(int i=0;i<gates.size();++i)
    {
        flip = ToffoliGate(a[gates[i].getLoc1()],b[gates[i].getLoc2()]);
        if(flip)
        {
            solution.flip(gates[i].getLoc3());
        }
    }
}

bool Solver::ToffoliGate(int x, int y)
{
    if(x && y)
    {
        return true;
    }
    return false;
}

int Solver::getFitness()
{
    return fitness;
}

void Solver::calculateFitness(bitset<16> temp, unsigned int limit)
{
    fitness = 0;
    for(int i=0;i<limit;++i)
    {
        if(solution[i] == temp[i])
        {
            ++fitness;
        }
    }
}
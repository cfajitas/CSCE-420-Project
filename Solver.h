#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<vector>

#include "Gate.h"
using namespace std;

class Solver
{
private:
    vector<Gate> gates;
    bitset<16> solution;
    int fitness;
public:
    Solver();
    void addGate(Gate g);
    void calculateSolution(bitset<16> a, bitset<16> b);
    bool ToffoliGate(int x, int y);
    int getFitness();
    void calculateFitness(bitset<16> temp, unsigned int limit);
};
#endif
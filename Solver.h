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
    bool solution;
public:
    Solver();
    void addGate(Gate g);
    bool isSolution();
    void checkSolution(unsigned int a, unsigned int b, unsigned int c);
};
#endif
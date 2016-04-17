#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<vector>
#include<bitset>
#include<limits.h>
#include<algorithm>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "Circuit.h"

using namespace std;

class Solver
{
private:
    vector<bitset<16>> pvec;
    vector<bitset<16>> qvec;
    vector<bitset<32>> nvec;
    int plimit;
    int qlimit;
    int nlimit;
    vector<int> nlimits;
    int nums;
    vector<Circuit> circuits;
    int numCircuits;
public:
    Solver();
    void addNum(bitset<16> p, bitset<16> q, bitset<32> n, int pl, int ql, int nl);
    void setUp(int numCircuits);
    void run();
    void addGates();
    void calcFitness();
    void revert();
    int checkDone();
    static bool sortFitness(const Circuit &l, const Circuit &r)
    {
    	return l.getFitness() > r.getFitness();
    }
};
#endif
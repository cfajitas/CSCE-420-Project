#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>

#include "Circuit.h"

using namespace std;

class Solver
{
private:
    vector<bitset<16>> pvec;
    vector<bitset<16>> qvec;
    vector<bitset<32>> nvec;
    vector<int> plimits;
    vector<int> qlimits;
    vector<int> nlimits;
    int nums;
    vector<Circuit> circuits;
public:
    Solver();
    void addNum(bitset<16> p, bitset<16> q, bitset<32> n, int pl, int ql, int nl);
    void run();
    
    
    void calcFitness();
    static bool sortFitness(const Circuit &l, const Circuit &r);
};
#endif
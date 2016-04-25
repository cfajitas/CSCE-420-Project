#ifndef PROBLEM_H
#define PROBLEM_H

#include<iostream>
#include<vector>
#include<bitset>
#include<algorithm>

using namespace std;

class Problem
{
private:
    bitset<30> pq;
    bitset<30> n;
    vector<int> limits;
public:
    Problem(int pn, int qn, int nn, int pl, int ql, int nl);
    bitset<30> getPQ();
    vector<int> getLimits();
    bool isSolution(bitset<30> num);
    int getFitness(bitset<30> num);
    void print();
};
#endif
#ifndef PROBLEM_H
#define PROBLEM_H

#include<iostream>
#include<vector>
#include<bitset>

using namespace std;

class Problem
{
private:
    int p;
    int q;
    int n;
    bitset<32> nset;
    vector<int> limits;
public:
    Problem(int n1, int n2, int n3, int pl, int ql, int nl);
    int getP();
    int getQ();
    vector<int> getLimits();
    bool isSolution(int num);
    int getFitness(int num);
    void print();
};
#endif
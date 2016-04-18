#ifndef PROBLEM_H
#define PROBLEM_H

#include<iostream>
#include<bitset>

using namespace std;

class Problem
{
private:
    int p;
    int q;
    int n;
    bitset<32> nset;
    int nlimit;
public:
    Problem(int n1, int n2, int n3, int nl);
    int getP();
    int getQ();
    bool isSolution(int num);
    int getFitness(int num);
    void print();
};
#endif
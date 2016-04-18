#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<vector>
#include<bitset>

using namespace std;

class Circuit
{
private:
    vector<int> loc1;
    vector<int> loc2;
    vector<int> loc3;
    long long int fitness;
    long long int fitnessOld;
    vector<int> flipped;
public:
    Circuit();
    void addGate(int l1, int l2, int l3);
    int runGates(int p, int q, vector<int> l);
    void drop();
    void cull();
    void setFitness(long long int f);
    long long int getFitness() const;
    void print();
};
#endif
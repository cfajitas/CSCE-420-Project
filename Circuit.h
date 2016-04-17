#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<vector>
#include<bitset>
#include<limits.h>

using namespace std;

class Circuit
{
private:
    vector<int> loc1;
    vector<int> loc2;
    vector<int> loc3;
    int numGates;
    long long int oldFitness;
    long long int fitness;
public:
    Circuit();
    void addGate(int l1, int l2, int l3);
    void runGates(vector<bitset<16>> p, vector<bitset<16>> q, vector<bitset<32>> n, vector<int> nlen, int size);
    vector<bitset<32>> getSolutions(vector<bitset<16>> p, vector<bitset<16>> q, vector<bitset<32>> n, int size);
    void fitnessRevert();
    void print();
    long long int getFitness() const;
};
#endif
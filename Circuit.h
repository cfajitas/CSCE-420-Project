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
    int numGates;
    long long int fitness;
public:
    Circuit();
    void addGate(int l1, int l2, int l3);
    bool runCircuit(bitset<16> p, bitset<16> q, bitset<32> n);
    
    long long int getFitness() const;
};
#endif
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>

#include "Gate.h"

using namespace std;

class Circuit
{
private:
    vector<Gate> gates;
    long long int fitness;
    long long int fitnessOld;
    vector<int> flipped;
public:
    Circuit();
    void addGate(Gate g);
    int resetFlip();
    bitset<30> runGates(bitset<30> pq);
    void revert();
    void cullUsed();
    void setFitness(long long int f);
    long long int getFitness() const;
    
    //vector<int> factorGates(vector<int> nl);
    
    void print(ofstream &out);
    void print();
};
#endif
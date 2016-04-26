#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
    int getGateNum();
    void deleteRandomGate(int i);
    vector<Gate> getGates();
    void setGates(vector<Gate> g);
    void setFitness(long long int f);
    long long int getFitness() const;
    bitset<30> factorGates(bitset<30> n);
    void print(ofstream &out);
    void print();
    
    static int random(int i){return rand()%i;}
};
#endif
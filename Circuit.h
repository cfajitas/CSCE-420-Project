//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Circuit.h

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

//This class holds a list of gates that may be a potential solution

class Circuit
{
private:
    vector<Gate> gates;
    long long int fitness;
    long long int fitnessOld;
    vector<int> flipped;
public:
    Circuit();
    Circuit(vector<Gate> g);
    void addGate(Gate g);
    int resetFlip();
    bitset<30> runGates(bitset<30> pq);
    void revert();
    void cullUsed();
    int getGateNum();
    void deleteRandomGate(int i);
    void mutateRandomGate(int i, int j);
    vector<Gate> getGates();
    void setFitness(long long int f);
    long long int getFitness() const;
    bitset<30> factorGates(bitset<30> n);
    void print(ofstream &out);
    void print();
};
#endif
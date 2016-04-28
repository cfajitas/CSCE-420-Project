//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Gate.h

#ifndef GATE_H
#define GATE_H

#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>

using namespace std;

//This class holds the info for a gate

class Gate
{
private:
    int n;
    vector<int> controllers;
    bool inverted;
public:
    Gate(int nl, vector<int> c, int invert);
    int getN();
    void setN(int nt);
    vector<int> getControllers();
    bool noControllers();
    bool getInverted();
    void print(ofstream &out);
    void print();
};
#endif
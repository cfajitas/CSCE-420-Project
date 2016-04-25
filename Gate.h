#ifndef GATE_H
#define GATE_H

#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>

using namespace std;

class Gate
{
private:
    int n;
    vector<int> controllers;
    bool inverted;
public:
    Gate(int nl, vector<int> c, int invert);
    int getN();
    vector<int> getControllers();
    bool noControllers();
    bool getInverted();
    void print(ofstream &out);
    void print();
};
#endif
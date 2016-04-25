#ifndef FACTORIZE_H
#define FACTORIZE_H

#include<iostream>
#include<fstream>
#include<bitset>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

#include "Circuit.h"

using namespace std;

class Factorize
{
private:
    vector<int> nlist;
    Circuit answer;
    vector<int> plist;
    vector<int> qlist;
public:
    Factorize(string file);
    void factorCircuit();
    void print();
};
#endif
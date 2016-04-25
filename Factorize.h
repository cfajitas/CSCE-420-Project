#ifndef FACTORIZE_H
#define FACTORIZE_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<bitset>
#include<vector>
#include<stdio.h>
#include<stdlib.h>

#include "Circuit.h"

using namespace std;

class Factorize
{
private:
    vector<bitset<30>> nlist;
    vector<bitset<30>> pqlist;
    Circuit answer;
public:
    Factorize(string file);
    void factorCircuit();
    void print();
};
#endif
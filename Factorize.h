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
public:
    Factorize(string file);
    
    void print();
};
#endif
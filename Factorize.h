//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Factorize.h

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

//This class reads in the N value and the solution and calculates the P Q values

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
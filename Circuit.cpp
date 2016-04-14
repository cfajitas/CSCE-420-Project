#include "Circuit.h"

Circuit::Circuit()
{
    numGates = 0;
    fitness = 0;
}

void Circuit::addGate(int l1, int l2, int l3)
{
    loc1.push_back(l1);
    loc2.push_back(l2);
    loc3.push_back(l3);
    ++numGates;
}

void Circuit::runGates(vector<bitset<16>> p, vector<bitset<16>> q, vector<bitset<32>> n, vector<int> nlen, int size)
{
    fitness=0;
    for(int i=0;i<size;++i)
    {
        bitset<32> temp = n[i];
        for(int j=0;j<numGates;++j)
        {
            if(p[i][loc1[j]] && q[i][loc2[j]])
            {
                n[i].flip(loc3[j]);
            }
        }
        for(int j=0;j<nlen[i];++j)
        {
            if(temp[j] == n[i][j])
            {
                ++fitness;
            }
        }
        if(temp == n[i])
        {
            fitness+=5;
        }
    }
}

long long int Circuit::getFitness() const
{
    return fitness;
}
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

bool Circuit::runCircuit(bitset<16> p, bitset<16> q, bitset<32> n)
{
    for(int i=0;i<numGates;++i)
    {
        if(p[loc1[i]] && q[loc2[i]])
        {
            n.flip(loc3[i]);
        }
    }
}

long long int Circuit::getFitness() const
{
    return fitness;
}
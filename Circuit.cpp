#include "Circuit.h"

Circuit::Circuit()
{
    numGates=0;
    fitness=0;
    oldFitness=0;
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
    oldFitness = fitness;
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
        cout<<"old n: "<<temp<<"\n";
        cout<<"new n: "<<n[i]<<"\n";
        cout<<"fitness: "<<fitness<<"\n";
        
    }
}

vector<bitset<32>> Circuit::getSolutions(vector<bitset<16>> p, vector<bitset<16>> q, vector<bitset<32>> n, int size)
{
    vector<bitset<32>> temp;
    for(int i=0;i<size;++i)
    {
        cout<<"old n: "<<n[i]<<"\n";
        
        for(int j=0;j<numGates;++j)
        {
            if(p[i][loc1[j]] && q[i][loc2[j]])
            {
                n[i].flip(loc3[j]);
            }
        }
        temp.push_back(n[i]);
        cout<<"new n: "<<temp[i]<<"\n";
    }
    return temp;
}

void Circuit::fitnessRevert()
{
    if(oldFitness > fitness)
    {
        
        cout<<"Old Fitness:"<<oldFitness<<"\n";
        cout<<"New Fitness:"<<fitness<<"\n";
        
        fitness = oldFitness;
        loc1.pop_back();
        loc2.pop_back();
        loc3.pop_back();
        --numGates;
    }
}

void Circuit::print()
{
    for(int i=0;i<numGates;++i)
    {
        cout<<"Loc1: "<<loc1[i]<<" ";
        cout<<"Loc2: "<<loc2[i]<<" ";
        cout<<"Loc3: "<<loc3[i]<<" ";
        cout<<"Fitness: "<<fitness<<"\n";
    }
}

long long int Circuit::getFitness() const
{
    return fitness;
}
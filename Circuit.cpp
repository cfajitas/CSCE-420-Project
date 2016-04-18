#include "Circuit.h"

Circuit::Circuit()
{
    fitness=0;
    fitnessOld=0;
}

void Circuit::addGate(int l1, int l2, int l3)
{
    loc1.push_back(l1);
    loc2.push_back(l2);
    loc3.push_back(l3);
}

int Circuit::runGates(int p, int q, vector<int> l)
{
    bitset<32> setP(p);
    bitset<32> setQ(q);
    bitset<32> n;
    for(int i=0;i<loc3.size();++i)
    {
        if(loc1[i] <= l[0] && loc2[i] <= l[1] && loc3[i] <= l[2])
        {
            if(setP[loc1[i]] && setQ[loc2[i]])
            {
                n.flip(loc3[i]);
            }
        }
    }
    return static_cast<int>(n.to_ulong());
}

void Circuit::drop()
{
    if(fitnessOld > fitness)
    {
        fitness = fitnessOld;
        fitnessOld = 0;
        loc1.pop_back();
        loc2.pop_back();
        loc3.pop_back();
    }
}

void Circuit::setFitness(long long int f)
{
    fitnessOld = fitness;
    fitness = f;
}

long long int Circuit::getFitness() const
{
    return fitness;
}

void Circuit::print()
{
    cout<<"Gates:\n";
    for(int i=0;i<loc3.size();++i)
    {
        cout<<"Loc1: "<<loc1[i]<<" Loc2: "<<loc2[i]<<" Loc3: "<<loc3[i]<<"\n";
    }
    cout<<"Fitness: "<<fitness<<"\n";
}
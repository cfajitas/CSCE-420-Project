#include "Circuit.h"

Circuit::Circuit()
{
    fitness=0;
    fitnessOld=0;
}

void Circuit::addGate(Gate g)
{
    gates.push_back(g);
    flipped.push_back(0);
}

int Circuit::resetFlip()
{
    for(int i=0;i<flipped.size();++i)
    {
        flipped[i] = 0;
    }
}

bitset<30> Circuit::runGates(bitset<30> pq)
{
    for(int i=0;i<gates.size();++i)
    {
        if(gates[i].noControllers())
        {
            pq.flip(gates[i].getN());
            flipped[i] = 1;
        }
        else
        {
            int flip = 1;
            vector<int> temp = gates[i].getControllers();
            for(int j=0;j<temp.size();++j)
            {
                if(flip)
                {
                    if(gates[i].getInverted())
                    {
                        if(pq[temp[j]])
                        {
                            flip = 0;
                        }
                    }
                    else
                    {
                        if(!(pq[temp[j]]))
                        {
                            flip = 0;
                        }
                    }
                }
            }
            if(flip)
            {
                pq.flip(gates[i].getN());
                flipped[i] = 1;
            }
        }
    }
    return pq;
}

void Circuit::revert()
{
    if(fitnessOld > fitness)
    {
        fitness = fitnessOld;
        fitnessOld = 0;
        gates.pop_back();
        flipped.pop_back();
    }
}

void Circuit::cullUsed()
{
    for(int i=flipped.size()-1;i>=0;--i)
    {
        if(!(flipped[i]))
        {
            flipped.erase(flipped.begin()+i);
            gates.erase(gates.begin()+i);
        }
    }
}

void Circuit::setFitness(long long int f)
{
    fitnessOld = fitness;
    fitness = f-gates.size();
}

long long int Circuit::getFitness() const
{
    return fitness;
}

/*
vector<int> Circuit::factorGates(vector<int> nl)
{
    vector<int> pq;
    for(int i=0;i<nl.size();++i)
    {
        bitset<32> p(0);
        bitset<32> q(0);
        bitset<32> n(nl[i]);
        for(int j=loc3.size()-1;j>=0;--j)
        {
            if(n[loc3[j]])
            {
                p.flip(loc1[j]);
                q.flip(loc2[j]);
            }
        }
        pq.push_back(static_cast<int>(p.to_ulong()));
        pq.push_back(static_cast<int>(q.to_ulong()));
    }
    return pq;
}
*/

void Circuit::print(ofstream &out)
{
    for(int i=0;i<gates.size();++i)
    {
        gates[i].print(out);
    }
    out<<"Fitness: "<<fitness<<"\n";
}

void Circuit::print()
{
    for(int i=0;i<gates.size();++i)
    {
        gates[i].print();
    }
    cout<<"Fitness: "<<fitness<<"\n";
    cout<<"NumGates: "<<gates.size()<<"\n";
}
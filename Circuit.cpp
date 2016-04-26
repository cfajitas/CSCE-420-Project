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

int Circuit::getGateNum()
{
    return gates.size();
}

void Circuit::deleteRandomGate(int i)
{
    if(!gates.empty())
    {
        gates.erase(gates.begin()+i);
        flipped.erase(flipped.begin()+i);
    }
}

vector<Gate> Circuit::getGates()
{
    return gates;
}

void Circuit::setGates(vector<Gate> g)
{
    gates = g;
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

bitset<30> Circuit::factorGates(bitset<30> n)
{
    for(int i=gates.size()-1;i>=0;--i)
    {
        if(gates[i].noControllers())
        {
            n.flip(gates[i].getN());
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
                        if(n[temp[j]])
                        {
                            flip = 0;
                        }
                    }
                    else
                    {
                        if(!(n[temp[j]]))
                        {
                            flip = 0;
                        }
                    }
                }
            }
            if(flip)
            {
                n.flip(gates[i].getN());
            }
        }
    }
    return n;
}

void Circuit::print(ofstream &out)
{
    out<<gates.size()<<"\n";
    for(int i=0;i<gates.size();++i)
    {
        gates[i].print(out);
    }
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
//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Circuit.cpp

#include "Circuit.h"

//Contructor sets the initial zero fitness
Circuit::Circuit()
{
    fitness=0;
    fitnessOld=0;
}

//Contructor for prexisting set of gates
Circuit::Circuit(vector<Gate> g)
{
    fitness=0;
    fitnessOld=0;
    gates = g;
    for(int i=0;i<gates.size();++i)
    {
        flipped.push_back(0);
    }
}

//Adds gate and check to see if gate is used
void Circuit::addGate(Gate g)
{
    gates.push_back(g);
    flipped.push_back(0);
}

//Resets check for gate use
int Circuit::resetFlip()
{
    for(int i=0;i<flipped.size();++i)
    {
        flipped[i] = 0;
    }
}

//Returns the result N after running PQ through all the gates
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

//If the most recent gate dropped the fitness, revert back
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

//Removes all unused gates that did not flip a bit for any pair of numbers
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

//Returns the size of the solution
int Circuit::getGateNum()
{
    return gates.size();
}

//Deletes a random gate in the solution
void Circuit::deleteRandomGate(int i)
{
    if(!gates.empty())
    {
        gates.erase(gates.begin()+i);
        flipped.erase(flipped.begin()+i);
    }
}

//Changes the controlled bit in a random gate in the solution
void Circuit::mutateRandomGate(int i, int j)
{
    if(!gates.empty())
    {
        gates[i].setN(j);
    }    
}

//returns the solution gates
vector<Gate> Circuit::getGates()
{
    return gates;
}

//Sets the current and previous fitness, subtracting the size of the solution from the fitness score
void Circuit::setFitness(long long int f)
{
    fitnessOld = fitness;
    fitness = f-gates.size();
}

//Returns the fitness score
long long int Circuit::getFitness() const
{
    return fitness;
}

//Runs the gates in reverse on N in order to return the P and Q values
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

//Prints the solution to a text file
void Circuit::print(ofstream &out)
{
    out<<gates.size()<<"\n";
    for(int i=0;i<gates.size();++i)
    {
        gates[i].print(out);
    }
}

//Prints the solution to the command line
void Circuit::print()
{
    for(int i=0;i<gates.size();++i)
    {
        gates[i].print();
    }
    cout<<"NumGates: "<<gates.size()<<"\n";
}
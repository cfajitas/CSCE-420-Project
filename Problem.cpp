//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Problem.cpp

#include "Problem.h"

//Contructor takes the P Q N values and their bit size without leading zeros
Problem::Problem(int pn, int qn, int nn, int pl, int ql, int nl)
{
    bitset<15> temp(pn);
    pq = bitset<30>(qn);
    for(int i=0;i<15;++i)
    {
        if(temp[i])
        {
            pq[i+15] = 1;
        }
    }
    n = bitset<30>(nn);
    for(int i=0;i<=nl;++i)
    {
        limits.push_back(i);
    }
    for(int i=0;i<=ql;++i)
    {
        limits.push_back(i);
    }
    for(int i=0;i<=pl;++i)
    {
        limits.push_back(i+15);
    }
    //Sorts and Removes extra bit spots so that the vector contains only bits that are relevant to the current numbers
    sort(limits.begin(),limits.end());
    limits.erase(unique(limits.begin(),limits.end()),limits.end());
}

//Returns PQ
bitset<30> Problem::getPQ()
{
    return pq;
}

//Returns bit locations relevant to the current problem
vector<int> Problem::getLimits()
{
    return limits;
}

//Checks if solution found is correct
bool Problem::isSolution(bitset<30> num)
{
    return n==num;
}

//Returns the fitness score for a N calculated from a solution
//If the number is a solution, returns the number of correct bits with a higher weight
//If the number is not a solution, returns the number of correct bits with a lower weight value
//However all weights are higher than the weight for the number of gates added later
int Problem::getFitness(bitset<30> num)
{
    if(isSolution(num))
    {
        return (limits[limits.size()]+1)*5;
    }
    else
    {
        int count=0;
        for(int i=0;i<30;++i)
        {
            if(n[i] && num[i])
            {
                ++count;
            }
        }
        return count*3;
    }
}

//Prints the solution to the command line
void Problem::print()
{
    cout<<"PQ:           "<<pq<<"\n";
    cout<<"N:            "<<n<<"\n";
}
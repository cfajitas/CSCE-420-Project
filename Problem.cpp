#include "Problem.h"

Problem::Problem(int n1, int n2, int n3, int nl)
{
    p = n1;
    q = n2;
    n = n3;
    nset = bitset<32>(n);
    nlimit = nl;
}

int Problem::getP()
{
    return p;
}

int Problem::getQ()
{
    return q;
}

bool Problem::isSolution(int num)
{
    return n==num;
}

int Problem::getFitness(int num)
{
    if(isSolution(num))
    {
        return (nlimit+1)*2;
    }
    else
    {
        bitset<32> temp(n);
        int count=0;
        for(int i=0;i<=nlimit;++i)
        {
            if(nset[i] && temp[i])
            {
                ++count;
            }
        }
        return count;
    }
}

void Problem::print()
{
    cout<<"P: "<<p<<" Q: "<<q<<" N: "<<n<<"\n";
    cout<<"Binary N: "<<nset<<"\n";
}
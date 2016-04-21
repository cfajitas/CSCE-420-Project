#include "Problem.h"

Problem::Problem(int n1, int n2, int n3, int pl, int ql, int nl)
{
    p = n1;
    q = n2;
    n = n3;
    nset = bitset<32>(n);
    limits.push_back(pl);
    limits.push_back(ql);
    limits.push_back(nl);
}

int Problem::getP()
{
    return p;
}

int Problem::getQ()
{
    return q;
}

vector<int> Problem::getLimits()
{
    return limits;
}

bool Problem::isSolution(int num)
{
    return n==num;
}

int Problem::getFitness(int num)
{
    if(isSolution(num))
    {
        return (limits[2]+1)*5;
    }
    else
    {
        bitset<32> temp(n);
        int count=0;
        for(int i=0;i<=limits[2];++i)
        {
            if(nset[i] && temp[i])
            {
                ++count;
            }
        }
        return count*3;
    }
}

void Problem::print()
{
    cout<<"Problem\n";
    cout<<"P: "<<p<<" Q: "<<q<<" N: "<<n<<"\n";
    cout<<"Binary P: "<<static_cast<bitset<32>>(p)<<"\n";
    cout<<"Binary Q: "<<static_cast<bitset<32>>(q)<<"\n";
    cout<<"Binary N: "<<nset<<"\n";
    cout<<"Plimit: "<<limits[0]<<" QLimit: "<<limits[1]<<" NLimit: "<<limits[2]<<"\n";
}
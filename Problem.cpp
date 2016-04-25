#include "Problem.h"

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
    sort(limits.begin(),limits.end());
    limits.erase(unique(limits.begin(),limits.end()),limits.end());
}

bitset<30> Problem::getPQ()
{
    return pq;
}

vector<int> Problem::getLimits()
{
    return limits;
}

bool Problem::isSolution(bitset<30> num)
{
    return n==num;
}

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

void Problem::print()
{
    cout<<"PQ: "<<pq<<"\n";
    cout<<"N:  "<<n<<"\n";
}
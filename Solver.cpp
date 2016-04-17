#include "Solver.h"

Solver::Solver()
{
    nums=0;
    plimit=0;
    qlimit=0;
    nlimit=0;
    numCircuits=0;
}

void Solver::addNum(bitset<16> p, bitset<16> q, bitset<32> n, int pl, int ql, int nl)
{
    pvec.push_back(p);
    qvec.push_back(q);
    nvec.push_back(n);
    if(pl > plimit)
    {
        plimit = pl;
    }
    if(ql > qlimit)
    {
        qlimit = ql;
    }
    if(nl > nlimit)
    {
        nlimit = nl;
    }
    nlimits.push_back(nl);
    ++nums;
}

void Solver::setUp(int n)
{
    numCircuits = n;
    for(int i=0;i<numCircuits;++i)
    {
        circuits.push_back(Circuit());
    }
}

void Solver::run()
{
    bool go = true;
    do
    {
        addGates();
        calcFitness();
        revert();
        int done = checkDone();
        if(done != -1)
        {
            go = false;
            circuits[done].print();
        }
    }while(go);
    
}

void Solver::addGates()
{
    int p=0;
    int q=0;
    int n=0;
    for(int i=0;i<numCircuits;++i)
    {
        p = rand()%plimit;
        q = rand()%qlimit;
        n = rand()%nlimit;
        circuits[i].addGate(p,q,n);
        
        
        cout<<"p loc: "<<p<<"\n";
        cout<<"q loc: "<<q<<"\n";
        cout<<"n loc: "<<n<<"\n";
        
        
    }
}

void Solver::calcFitness()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].runGates(pvec,qvec,nvec,nlimits,nums);
    }
    sort(circuits.begin(),circuits.end(),sortFitness);
}

void Solver::revert()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].fitnessRevert();
    }
}

int Solver::checkDone()
{
    int match = 1;
    vector<bitset<32>> temp;
    for(int i=0;i<circuits.size();++i)
    {
        temp = circuits[i].getSolutions(pvec,qvec,nvec,nums);
        for(int j=0;j<nvec.size();++j)
        {
            if(temp[j] != nvec[j])
            {
                match = 0;
            }
        }
        if(match == 1)
        {
            return i;
        }
        temp.clear();
        match=1;
    }
    return -1;
}
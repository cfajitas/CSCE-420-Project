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
    flipped.push_back(0);
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
                flipped[i] = 1;
            }
        }
    }
    return static_cast<int>(n.to_ulong());
}

int Circuit::resetFlip()
{
    for(int i=0;i<flipped.size();++i)
    {
        flipped[i] = 0;
    }
}

void Circuit::revert()
{
    if(fitnessOld > fitness)
    {
        fitness = fitnessOld;
        fitnessOld = 0;
        loc1.pop_back();
        loc2.pop_back();
        loc3.pop_back();
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
            loc1.erase(loc1.begin()+i);
            loc2.erase(loc2.begin()+i);
            loc3.erase(loc3.begin()+i);
        }
    }
}

void Circuit::cullDupes(vector<int> ps, vector<int> qs, vector<vector<int>> ls)
{
    vector<int> used;
    vector<int> safe;
    for(int i=0;i<32;++i)
    {
        used.push_back(0);
    }
    for(int i=0;i<loc3.size();++i)
    {
        safe.push_back(0);
    }
    for(int i=0;i<ps.size();++i)
    {
        bitset<32> setP(ps[i]);
        bitset<32> setQ(qs[i]);
        for(int j=0;j<loc3.size();++j)
        {
            if(loc1[j] <= ls[i][0] && loc2[j] <= ls[i][1] && loc3[j] <= ls[i][2])
            {
                if(setP[loc1[j]] && setQ[loc2[j]])
                {
                    ++used[loc3[j]];
                }
            }
        }
        /*
        for(int j=0;j<used.size();++j)
        {
            while(used[j] >= 2)
            {
                for(int k=loc3.size()-1;k>=0;--k)
                {
                    if(loc3[k] == j && !safe[k])
                    {
                        flipped.erase(flipped.begin()+k);
                        loc1.erase(loc1.begin()+k);
                        loc2.erase(loc2.begin()+k);
                        loc3.erase(loc3.begin()+k);
                        --used[j];
                        k=-1;
                    }
                }
            }
        }
        */
        
        for(int j=0;j<loc3.size();++j)
        {
            if(loc1[j] <= ls[i][0] && loc2[j] <= ls[i][1] && loc3[j] <= ls[i][2])
            {
                if(setP[loc1[j]] && setQ[loc2[j]])
                {
                    safe[j] = 1;
                }
            }
        }
        
        for(int j=0;j<32;++j)
        {
            used[j] = 0;
        }
    }
}

void Circuit::setFitness(long long int f)
{
    fitnessOld = fitness;
    fitness = f;
}

long long int Circuit::getFitness() const
{
    return fitness-loc3.size();
}

void Circuit::print()
{
    cout<<"Gates:\n";
    for(int i=0;i<loc3.size();++i)
    {
        cout<<"Loc1: "<<loc1[i]<<" Loc2: "<<loc2[i]<<" Loc3: "<<loc3[i]<<" Flipped: "<<flipped[i]<<"\n";
    }
    cout<<"Number of Gates: "<<loc3.size()<<"\n";
    cout<<"Fitness: "<<fitness<<"\n";
}
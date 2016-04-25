#include "Factorize.h"

Factorize::Factorize(string file)
{
    ifstream in(file);
    string temp = "";
    getline(in,temp);
    int nNum = atoi(temp.c_str());
    for(int i=0;i<nNum;++i)
    {
        getline(in,temp);
        nlist.push_back(bitset<30>(temp));
    }
    getline(in,temp);
    int gNum = atoi(temp.c_str());
    for(int i=0;i<gNum;++i)
    {
        getline(in,temp);
        stringstream ss(temp);
        int invert = 0;
        int n = 0;
        int temp = 0;
        ss >> invert;
        ss >> n;
        vector<int> locs;
        while(ss >> temp)
        {
            locs.push_back(temp);
        }
        Gate g(n,locs,invert);
        answer.addGate(g);
    }
}

void Factorize::factorCircuit()
{
    for(int i=0;i<nlist.size();++i)
    {
        pqlist.push_back(answer.factorGates(nlist[i]));
    }
}

void Factorize::print()
{
    for(int i=0;i<nlist.size();++i)
    {
        cout<<"N:  "<<nlist[i]<<"\n";
    }
    for(int i=0;i<pqlist.size();++i)
    {
        cout<<"PQ: "<<pqlist[i]<<"\n";
    }
    answer.print();
}
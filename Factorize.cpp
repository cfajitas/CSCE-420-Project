//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Factorize.cpp

#include "Factorize.h"

//Contructor reads in the N values and Gates for a solution from the given text file
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


//Calculates the PQ value from running the gates solution in reverse
void Factorize::factorCircuit()
{
    for(int i=0;i<nlist.size();++i)
    {
        pqlist.push_back(answer.factorGates(nlist[i]));
    }
}

//Prints out the P Q valuea and the N they were factored from
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
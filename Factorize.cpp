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
        nlist.push_back(atoi(temp.c_str()));
    }
    in.ignore(1);
    int pl = 0;
    int ql = 0;
    int nl = 0;
    while(in>>pl>>ql>>nl)
    {
        answer.addGate(pl,ql,nl);
    }
}

void Factorize::print()
{
    for(int i=0;i<nlist.size();++i)
    {
        cout<<nlist[i]<<"\n";
    }
    answer.print();
}
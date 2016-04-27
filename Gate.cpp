#include "Gate.h"

Gate::Gate(int nl, vector<int> c, int invert)
{
    n = nl;
    for(int i=0;i<c.size();++i)
    {
        controllers.push_back(c[i]);
    }
    if(invert)
    {
        inverted = true;
    }
    else
    {
        inverted = false;
    }
}

int Gate::getN()
{
    return n;
}

void Gate::setN(int nt)
{
    n = nt;
}

vector<int> Gate::getControllers()
{
    return controllers;
}

bool Gate::noControllers()
{
    if(controllers.empty())
    {
        return true;
    }
    return false;
}

bool Gate::getInverted()
{
    return inverted;
}

void Gate::print(ofstream &out)
{
    if(inverted)
    {
        out<<1<<" ";
    }
    else
    {
        out<<0<<" ";
    }
    out<<n<<" ";
    for(int i=0;i<controllers.size();++i)
    {
        out<<controllers[i]<<" ";
    }
    out<<"\n";
}

void Gate::print()
{
    if(inverted)
    {
        cout<<1<<" ";
    }
    else
    {
        cout<<0<<" ";
    }
    cout<<n<<" ";
    for(int i=0;i<controllers.size();++i)
    {
        cout<<controllers[i]<<" ";
    }
    cout<<"\n";
}
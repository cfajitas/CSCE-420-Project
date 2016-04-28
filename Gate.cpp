//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Gate.cpp

#include "Gate.h"

//Contructor takes in the controlled bit, controller bits, and inverted bool
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

//Return the controlled bit
int Gate::getN()
{
    return n;
}

//Change the controlled bit
void Gate::setN(int nt)
{
    n = nt;
}

//Get the controller bits
vector<int> Gate::getControllers()
{
    return controllers;
}

//If no controller bits, returns true to flip controlled bit
bool Gate::noControllers()
{
    if(controllers.empty())
    {
        return true;
    }
    return false;
}

//Return inverted bool
bool Gate::getInverted()
{
    return inverted;
}

//Prints solution to text file
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

//Prints solution to command line
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
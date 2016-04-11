#include "Gate.h"

Gate::Gate()
{
    loc1=0;
    loc2=0;
    loc3=0;
}

Gate::Gate(unsigned int l1, unsigned int l2, unsigned int l3)
{
    loc1=l1;
    loc2=l2;
    loc3=l3;
}

unsigned int Gate::getLoc1()
{
    return loc1;
}

unsigned int Gate::getLoc2()
{
    return loc2;
}

unsigned int Gate::getLoc3()
{
    return loc3;
}
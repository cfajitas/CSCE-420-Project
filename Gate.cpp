#include "Gate.h"

Gate::Gate()
{
    loc1 = 0;
    loc2 = 0;
    loc3 = 0;
}

Gate::Gate(unsigned short l1, unsigned short l2, unsigned short l3)
{
    loc1 = l1;
    loc2 = l2;
    loc3 = l3;
}

unsigned short Gate::getLoc1()
{
    return loc1;
}

unsigned short Gate::getLoc2()
{
    return loc2;
}

unsigned short Gate::getLoc3()
{
    return loc3;
}
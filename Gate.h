#ifndef GATE_H
#define GATE_H

#include<iostream>

using namespace std;
class Gate
{
private:
    unsigned short loc1;
    unsigned short loc2;
    unsigned short loc3;
public:
    Gate();
    Gate(unsigned short l1, unsigned short l2, unsigned short l3);
    unsigned short getLoc1();
    unsigned short getLoc2();
    unsigned short getLoc3();
    
};
#endif
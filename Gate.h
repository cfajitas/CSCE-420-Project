#ifndef GATE_H
#define GATE_H
#include<iostream>
using namespace std;
class Gate
{
private:
    unsigned int loc1;
    unsigned int loc2;
    unsigned int loc3;
public:
    Gate();
    Gate(unsigned int l1, unsigned int l2, unsigned int l3);
    unsigned int getLoc1();
    unsigned int getLoc2();
    unsigned int getLoc3();
};
#endif
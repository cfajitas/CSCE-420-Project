#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>

#include "Solver.h"
#include "Gate.h"
using namespace std;

unsigned int getSize(bitset<16> temp);

int main()
{
    cout<<"Hello Cloud9 A* Code Here \n";
    unsigned int limitA = 0;
    unsigned int limitB = 0;
    unsigned int limitC = 0;
    cin>>limitA;
    cin>>limitB;
    cin>>limitC;
    bitset<16> num1(limitA);
    bitset<16> num2(limitB);
    bitset<16> num3(limitC);
    limitA = getSize(num1);
    limitB = getSize(num2);
    limitC = getSize(num3);
    return 0;
}

unsigned int getSize(bitset<16> temp)
{
    for(unsigned int i=15;i>=0;--i)
    {
        if(temp[i] == 1)
        {
            return i;
        }
    }
    return 0;
}
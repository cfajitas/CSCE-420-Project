#include<iostream>
#include<fstream>
#include<bitset>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "Solver.h"
#include "Circuit.h"

using namespace std;

int getSize(bitset<16> temp);
int getSize(bitset<32> temp);

int main()
{
    srand(time(NULL));
    Solver solve;
    int A = 0;
    int B = 0;
    int C = 0;
    while(cin>>A>>B>>C)
    {
        bitset<16> num1(A);
        bitset<16> num2(B);
        bitset<32> num3(C);
        A = getSize(num1);
        B = getSize(num2);
        C = getSize(num3);
        solve.addNum(num1,num2,num3,A,B,C);
    }
    
    int numCircuits = 5;
    
    solve.setUp(numCircuits);
    solve.run();
        
    
    return 0;
}

int getSize(bitset<16> temp)
{
    for(int i=15;i>=0;--i)
    {
        if(temp[i] == 1)
        {
            return i;
        }
    }
    return 0;
}

int getSize(bitset<32> temp)
{
    for(int i=31;i>=0;--i)
    {
        if(temp[i] == 1)
        {
            return i;
        }
    }
    return 0;
}
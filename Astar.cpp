#include<iostream>
#include<fstream>
#include<bitset>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Problem.h"
#include "Solver.h"

using namespace std;

int getSize(int num);

int main()
{
    srand(time(NULL));
    int A = 0;
    int B = 0;
    int C = 0;
    Solver solve(100);
    while(cin>>A>>B>>C)
    {
        int sizeN = getSize(C);
        Problem temp(A,B,C,sizeN);
        solve.addProblem(temp,getSize(A),getSize(B),sizeN);
    }
    
    solve.run();
    
    
    return 0;
}

int getSize(int num)
{
    bitset<32> temp(num);
    for(int i=31;i>=0;--i)
    {
        if(temp[i])
        {
            return i;
        }
    }
    return 0;
}
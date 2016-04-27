#include<iostream>
#include<fstream>
#include<bitset>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Problem.h"
#include "Gate.h"
#include "Circuit.h"
#include "Solver.h"
#include "Factorize.h"

using namespace std;

int getSize(int num);

int main()
{
    srand(time(NULL));
    int A = 0;
    int B = 0;
    int C = 0;
    Solver solve(1000);
    while(cin>>A>>B>>C)
    {
        int sizeP = getSize(A);
        int sizeQ = getSize(B);
        int sizeN = getSize(C);
        Problem temp(A,B,C,sizeP,sizeQ,sizeN);
        solve.addProblem(temp);
    }
    solve.runGenetic();
    solve.print("Output.txt");
    solve.print();
    
    Factorize factor("Output.txt");
    factor.factorCircuit();
    factor.print();
    
    
    return 0;
}

int getSize(int num)
{
    bitset<30> temp(num);
    for(int i=29;i>=0;--i)
    {
        if(temp[i])
        {
            return i;
        }
    }
    return 0;
}
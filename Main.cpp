//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Main.cpp

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

//Main Function is longer than 24 lines due to the need to get user input
int main()
{
    srand(time(NULL));
    string temp = "";
    cout<<"Please Enter Input file:\n";
    getline(cin,temp);
    string file = temp;
    cout<<"Please Enter:\n1 for Genetic\n2 for Astar\nAnything else will exit\n";
    getline(cin,temp);
    ifstream in(file);
    int A = 0;
    int B = 0;
    int C = 0;
	int gateLimit = 0;
	if(temp == "1")
	{
		gateLimit = 1000;
	}
	if(temp == "2")
	{
		gateLimit = 10000;
	}
    Solver solve(gateLimit);
    //Loop takes in all P Q N in the text file
    while(in>>A>>B>>C)
    {
        int sizeP = getSize(A);
        int sizeQ = getSize(B);
        int sizeN = getSize(C);
        Problem temp(A,B,C,sizeP,sizeQ,sizeN);
        solve.addProblem(temp);
    }
    in.close();
    if(temp == "1")
    {
        cout<<"\nRunning Genetic Algorithm\n";
        solve.runGenetic();
    }
    else if(temp == "2")
    {
        cout<<"\nRunning AStar Algorithm\n";
        solve.runAStar();
    }
    else
    {
        cout<<"Exiting\n";
        return 0;
    }
    //Prints out solution found
    string outFile = file+"_Output.txt";
    solve.print(outFile);
    solve.print();
    //Reads in solution and factorizes the N back into P and Q
    cout<<"\nFactoring Solution\n";
    Factorize factor(outFile);
    factor.factorCircuit();
    factor.print();
    return 0;
}

//Returns the number of bits in a number without leading zeros
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
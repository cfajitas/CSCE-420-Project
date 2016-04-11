#include<iostream>
#include<fstream>
#include<bitset>

#include "Solver.h"
#include "Gate.h"

using namespace std;
int main()
{
    cout<<"Hello Cloud9 A* Code Here \n";
    unsigned int A = 0;
    unsigned int B = 0;
    unsigned int C = 0;
    cin>>A;
    cin>>B;
    cin>>C;
    cout<<A<<"\n";
    cout<<B<<"\n";
    cout<<C<<"\n";
    cout<<bitset<16>(A)<<"\n";
    cout<<bitset<16>(B)<<"\n";
    cout<<bitset<16>(C)<<"\n";
    
    /* changes bit in '0-15' position by changing second 1
    A ^= 1 << 1;
    cout<<bitset<16>(A)<<"\n";
    A ^= 1 << 1;
    cout<<bitset<16>(A)<<"\n";
    */
    
    cout<<"\n\n";
    
    bitset<16> test1(7);
    bitset<16> test2(13);
    bitset<16> test3(91);
    
    cout<<test1<<"\n";
    cout<<test2<<"\n";
    cout<<test3<<"\n";
    
    
    
    
    return 0;
}
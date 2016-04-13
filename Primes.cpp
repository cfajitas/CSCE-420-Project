#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main()
{
    ofstream out("Primes.txt");
    bool prime=false;
    out<<"2\n";
    out<<"3\n";
    out<<"5\n";
    for(int i=2;i<65535;++i)
    {
        prime=true;
        if(i%2 == 0 || i%3 == 0 || i%5 == 0)
        {
            prime=false;
        }
        else
        {
            for(int j=2;j<i;++j)
            {
                if(i%j == 0)
                {
                    prime = false;
                    break;
                }
            }
        }
        if(prime)
        {
            out<<i<<"\n";
        }
    }
    out.close();
    return 0;
}
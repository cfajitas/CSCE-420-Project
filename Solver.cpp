#include "Solver.h"

Solver::Solver(int nc)
{
    for(int i=0;i<nc;++i)
    {
        circuits.push_back(Circuit());
    }
    limits.push_back(0);
    limits.push_back(0);
    limits.push_back(0);
}

void Solver::addProblem(Problem p, int sizeP, int sizeQ, int sizeN)
{
    problems.push_back(p);
    if(sizeP > limits[0])
        limits[0] = sizeP;
    if(sizeQ > limits[1])
        limits[1] = sizeQ;
    if(sizeN > limits[2])
        limits[2] = sizeN;
}

void Solver::run()
{
    bool go = true;
    int loc = -1;
    do
    {
        addGates();
        loc = checkSolution();
        calcFitness();
        if(loc != -1)
        {
            cout<<"FOUND SOLUTION \n";
            print(loc);
            go = false;
        }
        else
        {
            printTest();
            revert();
        }
    }while(go);
}

void Solver::addGates()
{
    for(int i=0;i<circuits.size();++i)
    {
        int pl = rand()%(limits[0]+1);
        int ql = rand()%(limits[1]+1);
        int nl = rand()%(limits[2]+1);
        circuits[i].addGate(pl,ql,nl);
    }
}

int Solver::checkSolution()
{
    for(int i=0;i<circuits.size();++i)
    {
        bool solution  = true;
        for(int j=0;j<problems.size();++j)
        {
            int n = circuits[i].runGates(problems[j].getP(),problems[j].getQ());
            if(!(problems[j].isSolution(n)))
            {
                solution = false;
            }
        }
        if(solution)
        {
            return i;
        }
        solution = true;
    }
    return -1;
}

void Solver::calcFitness()
{
    for(int i=0;i<circuits.size();++i)
    {
        long long int temp=0;
        for(int j=0;j<problems.size();++j)
        {
            int n = circuits[i].runGates(problems[j].getP(),problems[j].getQ());
            temp+=problems[j].getFitness(n);
        }
        circuits[i].setFitness(temp);
    }
    sort(circuits.begin(),circuits.end(),sortFitness);
}

void Solver::revert()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].drop();
    }
}

void Solver::print(int cl)
{
    circuits[cl].print();
    for(int i=0;i<problems.size();++i)
    {
        cout<<"Current N: "<<circuits[cl].runGates(problems[i].getP(),problems[i].getQ())<<"\n";
        cout<<"Current NSET: "<<static_cast<bitset<32>>(circuits[cl].runGates(problems[i].getP(),problems[i].getQ()))<<"\n";
    }
}

void Solver::printTest()
{
    cout<<"TEST \n";
    circuits[0].print();
    for(int i=0;i<problems.size();++i)
    {
        cout<<"Current N: "<<circuits[0].runGates(problems[i].getP(),problems[i].getQ())<<"\n";
        cout<<"Current NSET: "<<static_cast<bitset<32>>(circuits[0].runGates(problems[i].getP(),problems[i].getQ()))<<"\n";
    }
}
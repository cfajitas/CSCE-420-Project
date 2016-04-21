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
    solutionLoc = 0;
}

void Solver::addProblem(Problem p)
{
    problems.push_back(p);
    vector<int> temp = p.getLimits();
    if(temp[0] > limits[0])
        limits[0] = temp[0];
    if(temp[1] > limits[1])
        limits[1] = temp[1];
    if(temp[2] > limits[2])
        limits[2] = temp[2]; 
}

void Solver::run()
{
    bool go = true;
    int loc = -1;
    do
    {
        addGates();
        calcFitness();
        clean();
        loc = checkSolution();
        if(loc != -1)
        {
            solutionLoc = loc;
            go = false;
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
        bool solution = true;
        circuits[i].resetFlip();
        for(int j=0;j<problems.size();++j)
        {
            int n = circuits[i].runGates(problems[j].getP(),problems[j].getQ(),problems[j].getLimits());
            solution = (solution && problems[j].isSolution(n));
        }
        if(solution)
        {
            return i;
        }
    }
    return -1;
}

void Solver::calcFitness()
{
    for(int i=0;i<circuits.size();++i)
    {
        long long int temp=0;
        circuits[i].resetFlip();
        for(int j=0;j<problems.size();++j)
        {
            int n = circuits[i].runGates(problems[j].getP(),problems[j].getQ(),problems[j].getLimits());
            temp+=problems[j].getFitness(n);
        }
        circuits[i].setFitness(temp);
    }
    sort(circuits.begin(),circuits.end(),sortFitness);
}

void Solver::clean()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].revert();
    }
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].cullUsed();
    }
}

int Solver::getSolutionLocation()
{
    return solutionLoc;
}

void Solver::printSolution(string file)
{
    circuits[solutionLoc].resetFlip();
    vector<int> nl;
    for(int i=0;i<problems.size();++i)
    {
        int n = circuits[solutionLoc].runGates(problems[i].getP(),problems[i].getQ(),problems[i].getLimits());
        nl.push_back(n);
    }
    circuits[solutionLoc].printGates(file,nl);
}

void Solver::print()
{
    circuits[solutionLoc].resetFlip();
    for(int i=0;i<problems.size();++i)
    {
        problems[i].print();
        int n = circuits[solutionLoc].runGates(problems[i].getP(),problems[i].getQ(),problems[i].getLimits());
        cout<<"Current N: "<<n<<"\n";
        cout<<"Current NSET: "<<static_cast<bitset<32>>(n)<<"\n";
    }
    circuits[solutionLoc].print();
}
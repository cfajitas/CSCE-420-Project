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
    for(int i=0;i<temp.size();++i)
    {
        limits.push_back(temp[i]);
    }
    sort(limits.begin(),limits.end());
    limits.erase(unique(limits.begin(),limits.end()),limits.end());
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
        print();
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
        int nl = limits[rand()%limits.size()];
        vector<int> c;
        int temp = rand()%3;
        for(int i=0;i<temp;++i)
        {
            c.push_back(limits[rand()%limits.size()]);
        }
        temp = rand()%2;
        Gate g(nl,c,temp);
        circuits[i].addGate(g);
    }
}

void Solver::calcFitness()
{
    for(int i=0;i<circuits.size();++i)
    {
        long long int temp=0;
        circuits[i].resetFlip();
        for(int j=0;j<problems.size();++j)
        {
            bitset<30> n = circuits[i].runGates(problems[j].getPQ());
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

int Solver::checkSolution()
{
    for(int i=0;i<circuits.size();++i)
    {
        bool solution = true;
        circuits[i].resetFlip();
        for(int j=0;j<problems.size();++j)
        {
            bitset<30> n = circuits[i].runGates(problems[j].getPQ());
            solution = (solution && problems[j].isSolution(n));
        }
        if(solution)
        {
            return i;
        }
    }
    return -1;
}

int Solver::getSolutionLocation()
{
    return solutionLoc;
}

void Solver::print(string file)
{
    ofstream out(file);
    circuits[solutionLoc].resetFlip();
    out<<problems.size()<<"\n";
    for(int i=0;i<problems.size();++i)
    {
        bitset<30> n = circuits[solutionLoc].runGates(problems[i].getPQ());
        out<<n<<"\n";
    }
    circuits[solutionLoc].print(out);
    out.close();
}

void Solver::print()
{
    circuits[solutionLoc].resetFlip();
    for(int i=0;i<problems.size();++i)
    {
        problems[i].print();
        bitset<30> n = circuits[solutionLoc].runGates(problems[i].getPQ());
        cout<<n<<"\n";
    }
    circuits[solutionLoc].print();
}
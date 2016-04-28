#include "Solver.h"

Solver::Solver(int gl)
{
    gateLimit = gl;
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

void Solver::runGenetic()
{
    int keep = gateLimit/5;
    for(int i=0;i<keep;++i)
    {
        circuits.push_back(Circuit());
    }
    addNewGates(keep);
    bool go = true;
    int loc = -1;
    unsigned long long int generation=0;
    do
    {
        ++generation;
        if(generation%100==0)
        {
            randomDelete();
        }
        if(generation%20==0)
        {
            crossover(keep);
        }
        if(generation%10==0)
        {
            mutate();
        }
        addNewGates(keep);
        calcFitness();
        runSortFitness();
        shrink();
        cull();
        loc = checkSolution();
        if(generation%1000 == 0)
        {
            cout<<"Generation: "<<generation<<"\n";
            cout<<"Num Gates:  "<<circuits[0].getGateNum()<<"\n";
        }
        if(loc != -1)
        {
            solutionLoc = loc;
            cout<<"Generation: "<<generation<<"\n";
            go = false;
        }
    }while(go);
}

void Solver::runAStar()
{
    for(int i=0;i<gateLimit;++i)
    {
        circuits.push_back(Circuit());
    }
    bool go = true;
    int loc = -1;
    unsigned long long int generation=0;
    do
    {
        ++generation;
        addGatesAstar();
        calcFitness();
        revert();
        runSortFitness();
        cull();
        loc = checkSolution();
        if(generation%1000 == 0)
        {
            cout<<"Generation: "<<generation<<"\n";
            cout<<"Num Gates:  "<<circuits[0].getGateNum()<<"\n";
        }
        if(loc != -1)
        {
            solutionLoc = loc;
            cout<<"Generation: "<<generation<<"\n";
            go = false;
        }
    }while(go);
}

void Solver::addNewGates(int k)
{
    for(int i=0;i<k;++i)
    {
        Circuit tempCircuit = circuits[i];
        int nl = limits[rand()%limits.size()];
        vector<int> c;
        int temp = rand()%3;
        for(int i=0;i<temp;++i)
        {
            c.push_back(limits[rand()%limits.size()]);
        }
        temp = rand()%2;
        Gate g(nl,c,temp);
        tempCircuit.addGate(g);
        circuits.push_back(tempCircuit);
    }
}

void Solver::mutate()
{
    for(int i=0;i<circuits.size();++i)
    {
        int loc = rand()%circuits[i].getGateNum();
        int temp = rand()%2;
        circuits[i].mutateRandomGate(loc,temp);
    }
}

void Solver::crossover(int k)
{
    if(k%2 == 0)
    {
        ++k;
    }
    for(int i=0;i<k;i+=2)
    {
        vector<Gate> g1 = circuits[i].getGates();
        vector<Gate> g2 = circuits[i+1].getGates();
        if(g1.size() >= 2 && g2.size() >= 2)
        {
            vector<Gate> g1h1;
            vector<Gate> g1h2;
            vector<Gate> g2h1;
            vector<Gate> g2h2;
            for(int j=0;j<g1.size()/2;++j)
            {
                g1h1.push_back(g1[j]);
            }
            for(int j=g1.size()-1;j>=g1.size()/2;--j)
            {
                g1h2.push_back(g1[j]);
            }
            for(int j=0;j<g2.size()/2;++j)
            {
                g2h1.push_back(g2[j]);
            }
            for(int j=g2.size()-1;j>=g2.size()/2;--j)
            {
                g2h2.push_back(g2[j]);
            }
            vector<vector<Gate>> crosses;
            crosses.push_back(vector<Gate>(g1h1));
            crosses.push_back(vector<Gate>(g2h1));
            crosses.push_back(vector<Gate>(g2h1));
            crosses.push_back(vector<Gate>(g1h1));
            crosses.push_back(vector<Gate>(g2h2));
            crosses.push_back(vector<Gate>(g2h1));
            crosses.push_back(vector<Gate>(g1h1));
            crosses.push_back(vector<Gate>(g1h2));
            crosses.push_back(vector<Gate>(g2h2));
            crosses.push_back(vector<Gate>(g1h2));
            for(int j=0;j<g1h1.size();++j)
            {
                crosses[5].push_back(g1h1[j]);
                crosses[9].push_back(g1h1[j]);
            }
            for(int j=0;j<g1h2.size();++j)
            {
                crosses[1].push_back(g1h2[j]);
                crosses[2].push_back(g1h2[j]);
                crosses[4].push_back(g1h2[j]);
            }
            for(int j=0;j<g2h1.size();++j)
            {
                crosses[6].push_back(g2h1[j]);
                crosses[8].push_back(g2h1[j]);
            }
            for(int j=0;j<g2h2.size();++j)
            {
                crosses[0].push_back(g2h2[j]);
                crosses[3].push_back(g2h2[j]);
                crosses[7].push_back(g2h2[j]);
            }
            for(int j=0;j<crosses.size();++j)
            {
                circuits.push_back(Circuit(crosses[j]));
            }
        }
    }
}

void Solver::randomDelete()
{
    for(int i=0;i<circuits.size();++i)
    {
        int loc = rand()%circuits[i].getGateNum();
        circuits[i].deleteRandomGate(loc);
    }
}

void Solver::shrink()
{
    if(circuits.size() > gateLimit)
    {
        circuits.erase(circuits.begin()+gateLimit,circuits.end());
    }
}

void Solver::addGatesAstar()
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

void Solver::revert()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].revert();
    }
}

void Solver::cull()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].cullUsed();
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
}

void Solver::runSortFitness()
{
    sort(circuits.begin(),circuits.end(),sortFitness);
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
        cout<<"Calculated N: "<<n<<"\n";
    }
    circuits[solutionLoc].print();
}
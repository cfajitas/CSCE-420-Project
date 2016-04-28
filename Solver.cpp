//Cory Fleitas
//CSCE 420-500
//Due: April 28, 2016
//Solver.cpp

#include "Solver.h"

//Contructor sets the max limit of possible solutions to test out
Solver::Solver(int gl)
{
    gateLimit = gl;
    solutionLoc = 0;
}

//Adds in all problems to solve and keeps track of potential bits that need to be used
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

//Runs the genetic algorithm
//Note: Longer than 24 lines due to extensive commenting needed
void Solver::runGenetic()
{
    //Uses top 20% of children
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
        //Randomly deletes a gate every 100 generations
        if(generation%100==0)
        {
            randomDelete();
        }
        //Gets all crosses for top 20% of children every 20 generations
        if(generation%20==0)
        {
            crossover(keep);
        }
        //Mutates a Random Gate every 10 generations
        if(generation%10==0)
        {
            mutate();
        }
        //Adds a new random Gate every generation
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

//Runs the genetic algorithm
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
        //algorithm adds new random gate every generation, and reverts if the fitness value goes lower
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

//Adds new random gate with a controlled bit, 0 1 or 2 controller bits, and inverted bool
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

//Randomly changes the controlled bit of a gate
void Solver::mutate()
{
    for(int i=0;i<circuits.size();++i)
    {
        int loc = rand()%circuits[i].getGateNum();
        int temp = rand()%2;
        circuits[i].mutateRandomGate(loc,temp);
    }
}

//Crosses over all pairs in the top 20% of solutions
//EX: 1 and 2, 3 and 4, etc.
//Note longer than 24 lines due to the extensive data modification needed to collect all 
//10 possible crosses resulting from 2 solutions
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

//Randomly deletes a gate
void Solver::randomDelete()
{
    for(int i=0;i<circuits.size();++i)
    {
        int loc = rand()%circuits[i].getGateNum();
        circuits[i].deleteRandomGate(loc);
    }
}

//Shrinks the solution vector back to the limit set at beginining
void Solver::shrink()
{
    if(circuits.size() > gateLimit)
    {
        circuits.erase(circuits.begin()+gateLimit,circuits.end());
    }
}

//Adds a random new gate to all the possible solutions
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

//If the most recent gate dropped the fitness score, throw it away
void Solver::revert()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].revert();
    }
}

//Removes all gates that do not flip a bit after running through all the pairs of numbers
void Solver::cull()
{
    for(int i=0;i<circuits.size();++i)
    {
        circuits[i].cullUsed();
    }
}

//Sets the fitness score for each solution
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

//Sorts the solution list and puts the best ones in the front
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

//Gets the location of a solution if one is found
int Solver::getSolutionLocation()
{
    return solutionLoc;
}

//Prints solution found to a text file
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

//Prints out solution to the command line
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
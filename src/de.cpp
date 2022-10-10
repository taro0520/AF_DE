#include "../inc/de.h"
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
ofstream filename_de("result/data_de.txt");
DE::DE(int runs,int population_size,int dimension,int generation,double f,double cr)
{
    this->runs=runs;
    this->mPopulation_size=population_size;
    this->mDimension=dimension;
    this->mGeneration=generation;
    this->mF=f;
    this->mCr=cr;

    unsigned seed;
    seed = (unsigned)time(NULL);
    srand(seed);
}
void DE::Initialize(vector<vector<double>>&solutions)
{
    for(int i=0;i<this->mPopulation_size;i++)
        for(int j=0;j<this->mDimension;j++)
            solutions[i][j]=this->lower+rnd_d(0,1)*(this->upper-this->lower);
}
void DE::Mutation(vector<vector<double>>solutions,
                vector<vector<double>>&mutation_solutions,
                int index)
{
    int r1,r2,r3;
    r1=-1;
    r2=-1;
    r3=-1;

    r1=rnd_i(index,r2,r3);
    r2=rnd_i(index,r1,r3);
    r3=rnd_i(index,r1,r2);
    for(int j=0;j<this->mDimension;j++)
        mutation_solutions[index][j]=solutions[r1][j]+this->mF*(solutions[r2][j]-solutions[r3][j]);

}
void DE::Crossover(vector<vector<double>>solutions,
                    vector<vector<double>>mutation_solutions,
                    vector<vector<double>>&trial_solutions,
                    int index)
{
    int rnd;
    rnd=rand()%this->mDimension;
    for(int j=0;j<this->mDimension;j++)
    {
        if(rnd_d(0,1)<this->mCr || j==rnd)
            trial_solutions[index][j]=mutation_solutions[index][j];
        else
            trial_solutions[index][j]=solutions[index][j];
    }
}
void DE::Selection(vector<vector<double>>&solutions,
                    vector<vector<double>>trial_solutions,
                    int index)
{
    double temp;
    temp=Compute_Ackley(trial_solutions[index]);
    if(temp<Compute_Ackley(solutions[index]))
        solutions[index]=trial_solutions[index];
    if(temp<this->best_val)
        this->best_val=temp;
}
double DE::Compute_Ackley(vector<double>solution)
{
    double ans,temp1,temp2;
    temp1=0;
    temp2=0;
    for(int i=0;i<this->mDimension;i++)
    {
        temp1+=solution[i]*solution[i];
        temp2+=cos(this->c*solution[i]);
    }
    ans=-1*(this->a)*exp(-1*(this->b)*sqrt((double)temp1/this->mDimension))-exp((double)temp2/this->mDimension)+this->a+exp(1);
    return ans;

    // for(int i=0;i<this->mDimension;i++)
    //     temp1+=solution[i]*solution[i];
    // return temp1;
}
int DE::rnd_i(int i,int a,int b)
{
    int rnd=-1;
    while(rnd==-1 || rnd==i || rnd==a || rnd==b)
        rnd=rand()%this->mPopulation_size;
    return rnd;
}
double DE::rnd_d(double down,double up)
{
    double rnd_d;
    rnd_d=(double)rand()*(up-down) / RAND_MAX + down;
    return rnd_d;
}
void DE::show(vector<vector<double>>solutions)
{
    for(int i=0;i<this->mPopulation_size;i++)
    {
        cout<<"Population:"<<i<<endl;
        for(int j=0;j<this->mDimension;j++)
            cout<<solutions[i][j]<<" ";
        cout<<endl;
    }
}
void DE::Output(vector<vector<double>>solutions)
{
    for(int i=0;i<this->mPopulation_size;i++)
    {
        for(int j=0;j<this->mDimension;j++)
            filename_de<<solutions[i][j]<<" ";
        filename_de<<Compute_Ackley(solutions[i])<<endl;
    }
    // 2D output
    //filename_de<<endl<<endl; 
    // 3D output
    filename_de<<endl;
}
void DE::run()
{
    int runs=0;
    double fitness_total=0;
    int temp;

    DWORD star_time = GetTickCount();
    while(runs<this->runs)
    {
        int Generation=this->mGeneration;
        vector<vector<double>>solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
        vector<vector<double>>mutation_solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
        vector<vector<double>>trial_solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
    
        Initialize(solutions);

        while(Generation--)
        {
            // Output(solutions);
            for(int i=0;i<this->mPopulation_size;i++)
            {
                Mutation(solutions,mutation_solutions,i);
                Crossover(solutions,mutation_solutions,trial_solutions,i);
                Selection(solutions,trial_solutions,i);
            }
            // filename_de<<this->mGeneration-Generation<<" "<<best_val<<endl;
        }
        fitness_total+=this->best_val;
        this->best_val=DBL_MAX;
        runs++;
    }
    DWORD end_time = GetTickCount();
    temp=(end_time - star_time)/1000;

    cout<<"=====[Ackley function]====="<<endl;
    cout<<"#Runs:"<<this->runs<<endl;
    cout<<"#Algorithm:Differential Evolution"<<endl;
    cout<<"#Population size:"<<this->mPopulation_size<<endl;
    cout<<"#Dimesion:"<<this->mDimension<<endl;
    cout<<"#Generation:"<<this->mGeneration<<endl;
    cout<<"#F:"<<this->mF<<endl;
    cout<<"#Cr:"<<this->mCr<<endl;
    cout<<"#Best Fitness Mean:"<<(double)fitness_total/this->runs<<endl;
    cout<<"#Cost Time:"<<temp<<"s"<<endl;
}
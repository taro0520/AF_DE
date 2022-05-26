#include "../inc/de.h"
#include <time.h>
#include <fstream>
#include <windows.h>
#include <cmath>
ofstream filename_de("result/data_de.txt");
DE::DE(int population_size,int dimension,double f,double cr)
{
    this->mPopulation_size=population_size;
    this->mDimension=dimension;
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
                vector<vector<double>>&mutation_solutions)
{
    int r1,r2,r3;
    r1=-1;
    r2=-1;
    r3=-1;
    for(int i=0;i<mPopulation_size;i++)
    {
        r1=rnd_i(i,r2,r3);
        r2=rnd_i(i,r1,r3);
        r3=rnd_i(i,r1,r2);
        for(int j=0;j<this->mDimension;j++)
            mutation_solutions[i][j]=solutions[r1][j]+this->mF*(solutions[r2][j]-solutions[r3][j]);
    }
}
void DE::Crossover(vector<vector<double>>solutions,
                    vector<vector<double>>mutation_solutions,
                    vector<vector<double>>&trial_solutions)
{
    int rnd;
    for(int i=0;i<this->mPopulation_size;i++)
    {
        rnd=rand()%this->mDimension;
        for(int j=0;j<this->mDimension;j++)
        {
            if(rnd_d(0,1)<this->mCr || j==rnd)
                trial_solutions[i][j]=mutation_solutions[i][j];
            else
                trial_solutions[i][j]=solutions[i][j];
        }
    }
}
void DE::Selection(vector<vector<double>>&solutions,
                    vector<vector<double>>trial_solutions)
{
    for(int i=0;i<this->mPopulation_size;i++)
        if(Compute_Ackley(trial_solutions[i])<Compute_Ackley(solutions[i]))
            solutions[i]=trial_solutions[i];
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
    ans=-1*(this->a)*exp(-1*(this->b)*sqrt((double)temp1/this->mDimension)-exp((double)temp2/this->mDimension))+this->a+exp(1);
    return ans;
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
}
void DE::run()
{
    int temp;
    int Evaluation=this->mDimension*10000;
    vector<vector<double>>solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
    vector<vector<double>>mutation_solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
    vector<vector<double>>trial_solutions(this->mPopulation_size,vector<double>(this->mDimension,0));
    DWORD star_time = GetTickCount();
    Initialize(solutions);
    while(Evaluation--)
    {
        Output(solutions);
        Mutation(solutions,mutation_solutions);
        Crossover(solutions,mutation_solutions,trial_solutions);
        Selection(solutions,trial_solutions);
    }
    DWORD end_time = GetTickCount();
    temp=(end_time - star_time)/1000;

    cout<<"=====[Ackley function]====="<<endl;
    cout<<"#Algorithm:Differential Evolution"<<endl;
    cout<<"#Population size:"<<this->mPopulation_size<<endl;
    cout<<"#Dimesion:"<<this->mDimension<<endl;
    cout<<"#F:"<<this->mF<<endl;
    cout<<"#Cr:"<<this->mCr<<endl;
    cout<<"#Solutions:"<<endl;
    show(solutions);
    cout<<"#Cost Time:"<<temp<<"s"<<endl;
}
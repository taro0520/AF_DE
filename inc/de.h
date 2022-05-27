#ifndef __DE_H__
#define __DE_H__
#include <iostream>
#include <vector>
#define PI 3.14
using namespace std;
class DE
{
public:
    DE(int population_size,int dimension,double f,double cr);
    void run();
private:
    void Initialize(vector<vector<double>>&solutions);
    void Mutation(vector<vector<double>>solutions,
                vector<vector<double>>&mutation_solutions);
    void Crossover(vector<vector<double>>solutions,
                vector<vector<double>>mutation_solutions,
                vector<vector<double>>&trial_solutions);
    void Selection(vector<vector<double>>&solutions,
                vector<vector<double>>trial_solutions);
    double Compute_Ackley(vector<double>solution);
    int rnd_i(int i,int a,int b);
    double rnd_d(double down,double up);
    void show(vector<vector<double>>solutions);
    void Output(vector<vector<double>>solutions);

    int mPopulation_size;
    int mDimension;
    double mF;
    double mCr;

    double best_val=INT_MAX;

    int lower=-32;
    int upper=32;

    //Ackley function
    int a=20;
    double b=0.2;
    double c=2*PI;
};

#endif
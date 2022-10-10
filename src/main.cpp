#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "de.h"

int main(int argc, char** argv)
{
	if(!strcmp(argv[1],"de"))
    { 
        int runs=stoi(argv[2]);
        int population_size=stoi(argv[3]);
        int dimension=stoi(argv[4]);
        int generation=stoi(argv[5]);
        double f=stod(argv[6]);
        double cr=stod(argv[7]);

        DE demachine(runs,population_size,dimension,generation,f,cr);
        demachine.run();
    }
}
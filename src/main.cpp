#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "de.h"

int main(int argc, char** argv)
{
	if(!strcmp(argv[1],"de"))
    { 
        int population_size=stoi(argv[2]);
        int dimension=stoi(argv[3]);
        int generation=stoi(argv[4]);
        double f=stod(argv[5]);
        double cr=stod(argv[6]);

        DE demachine(population_size,dimension,generation,f,cr);
        demachine.run();
    }
}
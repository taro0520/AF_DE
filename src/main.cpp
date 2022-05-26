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
        double f=stod(argv[4]);
        double cr=stod(argv[5]);

        DE demachine(population_size,dimension,f,cr);
        demachine.run();
    }
}
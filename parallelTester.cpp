#include <omp.h>
#include <iostream>
#include <random>
#include <stdio.h>

using namespace std;

double fRand(double x){
	default_random_engine generator;
	normal_distribution<double> distribution(0, 1);
	double f=(double)rand()/RAND_MAX;
	return -x+f*2*x;
}

int main(int argc, char** argv) {
	
	double pom=0;

	#pragma omp parallel
    	printf("%f Hello!n\n", pom);
    
    #pragma omp parallel for 
		for(int n=0; n<250; ++n) {
			printf("%f Wubba Lubba Dub Dub\n", pom);
			pom+=fRand(1);
		}
		printf("\n");

	system("pause");
	return 0;
};

#include<iostream>
#include<cstdlib>
#include<fstream>
#include "function_list.h"
#include<omp.h>

//Main file to run for various values of p

using namespace std;

int main()
{
	float p = 0.592746;
	float time1,time2;
	
	//	while ( p <= 0.4)
	{
		time1 = omp_get_wtime();
		cluster_size(p);
		time2 = omp_get_wtime();
		cout << "Time for running a parallel HK algotithm for p = " <<
				p << "is = " << (time2 - time1) << endl;
		//	p += 0.1;
	}
	
	return 0;
}
	
	

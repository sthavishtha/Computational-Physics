#include<iostream>
#include<sys/time.h>
#include<stdlib.h> //for srand, drand48
#include<cmath>
#include<fstream>

using namespace std;

int main(int argc, char** argv)
{
  double x_new = 0,y_new = 0,theta;
  double r_sq_avg,r_sq_sq_avg, error, diff = 0., dist;
  double r_sq = 0., r_sq_sq = 0.;
  int j = 0, M = 1000;
  char filename[20];

  ofstream fout;
  //fout.open("simple_rand_walk_error.dat");

  //  fout << "N" << "\t" << "(Error/Average of R_2)" << "\t" << "Average of R_2" << "\t" << "M" << endl;
  
  srand48(time(NULL));
 
  
 for(int N =  100; N <= 300; N += 100)
 {
	
 r_sq = 0.; 
 r_sq_sq = 0.;
 M = 1000;
 j = 0;

 sprintf(filename,"simple_rand_walk_error%06d.dat",N);

 fout.open(filename);
 
 while(j < M)
   {

	    x_new = 0.;
	    y_new = 0.;

      for( int i = 0; i < N; i++)
	{
	  theta = 2*M_PI*drand48();
	  x_new = x_new + cos(theta); //step size taken to be 1
	  y_new = y_new + sin(theta);
	}
    
      dist = (x_new)*(x_new) + (y_new)*(y_new);
      r_sq += dist;
      r_sq_sq += dist*dist;

//      cout << r_sq/M << "\t "<< r_sq_sq/M << endl;
       if ( j == M-1)
	{
	  r_sq_avg = r_sq/M;
	  r_sq_sq_avg = r_sq_sq/M;

	  diff = (fabs(r_sq_avg - r_sq_sq_avg))/M;
	  error = sqrt(diff);
//	  cout << error << endl;

	  if(error > 0.01*r_sq_avg)
	    M++;

	  } 
       // cout << r_sq/M << endl;
       //	cout << r_sq_sq/M << endl;

      j++;
      fout << N << "\t" << (error/r_sq_avg) << "\t" << r_sq_avg << "\t" << M << endl;
    }

  cout << N << "\t" << r_sq_avg << "\t" << r_sq_sq_avg << "\t" << M << endl;
//  fout << N << "\t" << (error/r_sq_avg) << "\t" << r_sq_avg << "\t" << M << endl;
//  cout << "Reached" << endl;

  fout.close();
 
 }

 // fout.close();

  return 0;
}


  
  

#include<iostream>
#include<sys/time.h>
#include<stdlib.h> //for srand, drand48
#include<cmath>
#include<fstream>

using namespace std;

int chk_distance(double a, double b, double c, double d, double e, double f)
{
  double dist;
  dist = sqrt((a-b)*(a-b) + (c-d)*(c-d) + (e - f)*(e-f));
  
  return dist;
}

int coincide_sphere(double *x, double *y, double *z, int index)
{
  int i = 0, j, counter = 0;
  while( i < index)
    {
      j = chk_distance(x[i], x[index], y[i], y[index], z[i], z[index]);
		if( j < 2) //distance btw them less than 2 times radius
		{
		  counter = 1;
		  break;
		}
      i++;
    }

  return(counter); //if its 0, no coincide of spheres
}
	

int main(int argc, char** argv)
{
  double* x_new, *y_new, *z_new,theta, phi;
  double r_sq_avg,r_sq_sq_avg, error, diff = 0., dist;
  double r_sq = 0., r_sq_sq = 0.;
  int j = 0, M = 10, chk;

  ofstream fout, fout_error;
  fout.open("error_vs_m_n300_3D.dat");

  //  fout << "N" << "\t" << "(Error/Average of R_2)" << "\t" << "Average of R_2" << "\t" << "M" << endl;
  
  srand48(time(NULL));

if(1)
  {
    int N = 300;
    //    for(int N =  100; N <= 1e5; N += 200)
    {
	r_sq = 0.; 
	r_sq_sq = 0.;
	j = 0;
	M = 10;

	x_new = new (nothrow) double[N];
	y_new = new (nothrow) double[N];
	z_new = new (nothrow) double[N];	
  
	while(j < M)
	{

	    x_new[0] = 0.;
	    y_new[0] = 0.;
	    z_new[0] = 0.;
	    
	    for( int i = 0; i < N; i++)
	    {
		theta = 2*M_PI*drand48();
		phi = M_PI*drand48();
		x_new[i+1] = x_new[i] + 2*sin(phi)*cos(theta); //step size taken to be 1
		y_new[i+1] = y_new[i] + 2*sin(phi)*sin(theta);
		z_new[i+1] = z_new[i] + 2*cos(phi);

		//		cout << x_new[i+1] << "\t" << y_new[i+1] << "\t" << z_new[i+1] << endl;

		//		chk = coincide_sphere(x_new, y_new, z_new, i + 1);

		//	cout << chk << endl;

		if(chk == 1)
		  i--;
	    }

	    dist = (x_new[N-1])*(x_new[N-1]) + (y_new[N-1])*(y_new[N-1]) + (z_new[N-1]*z_new[N-1]);
	    r_sq += dist;
	    r_sq_sq += dist*dist;

	    //cout << x_new[N-1] << "\t" << y_new[N-1] << "\t" << z_new[N-1] << endl;

	    if ( j == M-1)
	    {
			r_sq_avg = r_sq/M;
			r_sq_sq_avg = r_sq_sq/M;

			diff = (fabs(r_sq_avg*r_sq_avg - r_sq_sq_avg))/M;
			error = sqrt(diff);

			fout << (error/r_sq_avg) << "\t" << M << endl;
			  
			if(error > 0.01*r_sq_avg)
			  M++;
	  
	    }
		
	    /*		for(int i = 0; i < N; ++i)
		{
			x_new[i] = 0.;
			y_new[i] = 0.;
			z_new[i] = 0.;
			}*/

		j++;
		
		//if(M%1000 == 0)
		{
		  //	    cout << N << "\t" << r_sq_avg << "\t" << r_sq_sq_avg << "\t" << M << endl;
		}

	}
		
//	cout << "Loop end" << endl;
	
	delete[] x_new;
	delete[] y_new;
	delete[] z_new;

	cout << N << "\t" << r_sq_avg << "\t" << r_sq_sq_avg << "\t" << M << endl;
	//fout << N << "\t" << (error/r_sq_avg) << "\t" << r_sq_avg << "\t" << M << endl;

    }
	fout.close();

  }

  return 0;
}


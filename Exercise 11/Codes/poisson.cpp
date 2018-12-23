/**
   Author:          Sthavishtha Bhopalam Rajakumar
   Description:     Exercise 11 - 2D electrostatic Poisson equation
   Created/Updated :24-12-2017
 **/

#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>
#include<omp.h>

//#define N 50

using namespace std;


/**
 * @brief Initializes the variables

*/

inline void rho_initialize(int x, int y, int N, double* rho, double delta_x)
{
  rho[(x + 1)*N + y] = 1.0/(delta_x*delta_x);
  rho[(x - 1)*N + y] = 1.0/(delta_x*delta_x);
  rho[x*N + y + 1] = 1.0/(delta_x*delta_x);
  rho[x*N + y - 1] = 1.0/(delta_x*delta_x);
}

inline void phi_bcs(int N, double* phi, double delta_x)
{

#pragma omp parallel
  {
#pragma omp for collapse(2) nowait
  for(int i = 0; i < N; i += N-1)
    for(int j = 0; j < N; j++)
      phi[i*N + j] = 0.0;
	
#pragma omp for collapse(2)
  for(int j = 0; j < N; j += N-1)
    for(int i = 0; i < N; i++)
      phi[i*N + j] = 0.0;
  }
 
}

inline void jacobi(int N, double* phi_o, double* phi_n, double delta_x, double* rho)
{

  // excluding the first and last nodes - where BCs are implemeted
#pragma omp parallel for collapse(2) 
  for(int i = 1; i < N -1; i++)
    for(int j = 1; j < N - 1; j++)
      phi_n[i*N + j] = 0.25*(phi_o[(i + 1)*N + j] + phi_o[(i - 1)*N + j] +
			     phi_o[i*N + j + 1] + phi_o[i*N + j - 1]) +
			      0.25*delta_x*delta_x*rho[i*N + j];
  
}

/**
 * @brief Implements the Red-Block variation of Gauss Siedel method


*/

inline void gauss_siedel(int N, double* phi_o, double* phi_n, double delta_x, double* rho)
{
 #pragma omp parallel
  {
    for(int i = 1; i < N - 1; i++)
    {
      #pragma omp for
      for(int j = (i%2) + 1; j < N - 1; j += 2)
	{
	  phi_n[i*N + j] = 0.25*(phi_o[(i + 1)*N + j] + phi_o[i*N + j + 1]
				  + phi_o[(i - 1)*N + j] + phi_o[i*N + j - 1])
			     + 0.25*delta_x*delta_x*rho[i*N + j];
	}
    }


  for(int i = 1; i < N - 1; i++)
    {
      #pragma omp for
      for(int j = ((i + 1)%2) + 1; j < N - 1; j += 2)
	{
	  phi_n[i*N + j] = 0.25*(phi_n[(i + 1)*N + j] + phi_n[i*N + j + 1]
				  + phi_n[(i - 1)*N + j] + phi_n[i*N + j - 1])
			     + 0.25*delta_x*delta_x*rho[i*N + j];
	}
    }  
  /*
#pragma omp for collapse(2)
  for(int i = 1; i < N - 1; i++)
    for(int j = 1; j < N - 1; j++)
    phi_n[i*N + j] = phi_o[i*N + j]; */
  }
  
}

inline double conv_error(double* phi_new, double* phi_old, int N)
{
  double error = 0.0;
#pragma omp parallel for collapse(2) reduction(+:error)
  for(int i = 1; i < N - 1; i++)
    for(int j = 1; j < N - 1; j++)
      error += fabs(phi_old[i*N + j] - phi_new[i*N + j]);

  return error;
    
}

inline void equate(double* phi_old, double* phi_new, int N)
{
#pragma omp parallel for collapse(2)
  for(int i = 1; i < N - 1; i++)
    for(int j = 1; j < N - 1; j++)
      phi_old[i*N + j] = phi_new[i*N + j];
  
}

inline void file_print(double* phi_new, int N, double delta_x)
{
  ofstream fout;
  fout.open("potential.plt");

  fout << "TITLE=\"2D\" " << endl;
  fout << "VARIABLES=\"X\",\"Y\",\"U\"" << endl;
  fout << "ZONE T=\"BLOCK1\",I="<< N << ",J=" << N << ",F=POINT" << endl;

  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      fout << setprecision(5) << i*delta_x << " " << j*delta_x << " " <<
	phi_new[i*N + j] << endl;

  fout.close();
}

inline void error_print(double* phi_new, int N, int iteration, double error)
{
  ofstream fout;
  #ifdef _JACOBI
  fout.open("error_conv_jacobi.dat",ios::app);
  #endif
  #ifdef _GAUSS
  fout.open("error_conv_gauss_siedel.dat",ios::app);
  #endif
  
 for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
      fout << setprecision(5) << iteration << " " <<
	   error << endl;

 fout.close();
}
    

int main(int argc, char *argv[])
{
  int N = 100;
  double delta_x, phi_old[N*N] = {0.0}, phi_new[N*N] = {0.0}, rho[N*N] = {0.0};
  double x_o = 0.25, y_o = 0.25, error;
  int x_o_coord, y_o_coord, iteration = 0;
  
  delta_x = 1.0/(N - 1);
  x_o_coord = x_o/delta_x;
  y_o_coord = y_o/delta_x;
  rho_initialize(x_o_coord, y_o_coord, N, rho, delta_x);
  
  x_o = 0.5, y_o = 0.5;
  x_o_coord = x_o/delta_x;
  y_o_coord = y_o/delta_x; 
  rho_initialize(x_o_coord, y_o_coord, N, rho, delta_x);

  x_o = 0.75, y_o = 0.75;
  x_o_coord = x_o/delta_x;
  y_o_coord = y_o/delta_x; 
  rho_initialize(x_o_coord, y_o_coord, N, rho, delta_x);
  
  phi_bcs(N, phi_old, delta_x);

  //#pragma omp parallel
  {
    while(1)
      {
	#ifdef _JACOBI
	jacobi(N, phi_old, phi_new, delta_x, rho);
	#endif
	#ifdef _GAUSS
        gauss_siedel(N, phi_old, phi_new, delta_x, rho);
	#endif
	error = conv_error(phi_old, phi_new, N);
	equate(phi_old, phi_new, N);
	cout << setprecision(5) << error << endl;

	if(iteration % 200 == 0)
	  error_print(phi_new,N, iteration, error);
	
	if(error < 1e-5)
	  break;
	iteration++;
      }
  }
  cout << "Number of iterations = " << iteration;
  file_print(phi_new, N, delta_x);
  return 0;
}

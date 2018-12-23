
#include<iostream>
#include<cmath>
#include<fstream>
#include "function_list.h"

using namespace std;

int main(int argc, char **argv)
{

  int x_c = 250, y_c = 250, N = 501;
  int flag[N*N] = {0}, steps = 0, mass[N];
  float p = 0.592746; //computing fractal dimension at critical occupation probability
  
  //initializing mass corresponding to all radii as 0
  for(int i = 0; i < N; ++i)
    mass[i] = 0;

  while(steps < 100)
    {
      cluster_size(p, flag, N);
      center_occ_pos(flag, x_c, y_c, N);
    //computing the mass corresponding to various radii - printing it into a file
      for(int r = 3; r <= N; r+=10)
	mass_radius(x_c,y_c,r,flag,mass, N);
      cout << steps << endl;
      steps++;
    }

  cout << "Final" <<endl;
  float mass_r;
  for(int r = 3; r <= N; r+=10)
    {
      cout << mass[r] << endl;
      mass_r = (float)mass[r]/(float)steps;
      file_print(r, mass_r);
    }
    
  return 0;
}

/**
 * Description   : To implement the Sandbox method for finding the fractal dimension of a percolating cluster
   Author        : Sthavishtha Bhopalam Rajakumar
   Date modified : 28-12-2017
 **/

#include<iostream>
#include<cmath>
#include<fstream>
#include "function_list.h"

using namespace std;

/*returns the minimum among 2 integers - and finds the corresponding center positions of the occupied lattice sites */
void min(int a, int b, int *x, int *y, int k_ind)
{
  if(a > b)
    {
      *x = *x - k_ind;
      *y = *y;
    }
     
  else //works even when a=b, so any one is chosen
    {
      *x = *x + k_ind;
      *y = *y;
    }
}

//finds the position of an occupied site lying close to the center
void center_occ_pos(int flag[], int &x_c, int &y_c, int N)
{
  //  int distance_1 = 0, distance_2 = 0, k_var;
  //  int counter = 0;

  //if flag at the exact centre of the lattice is not 1
  if(flag[index(x_c,y_c, N)] != 1) 
    {
      /*if its a percolating cluster, there should be atleast one along the horizontal direction of x_c with a flag of 1 - that'y why max k limit is 250 */
      for(int j = -3; j < 3; ++j)
      for(int t = 1; t <= 250; ++t) 
       {
	 if(flag[index(x_c + j, y_c, N) + t] == 1)
	   {
	     x_c = x_c + j;
	     y_c = y_c + t;
	     //	     counter++;
	     //	     cout << "here" <<endl;
	     break;
	   }
	 if(flag[index(x_c + j, y_c, N) - t] == 1)
	   {
	     x_c = x_c + j;
	     y_c = y_c - t;
	     //	     counter++;
	     //	     cout << "here2" <<endl;
	     break;
	   }
       }
      
      //      min(distance_1, distance_2, &x_c, &y_c, t);
    }
  //    cout << x_c << "\t" << y_c << "\t" << flag[index(x_c,y_c, N)] << endl;
}
  

//prints the mass and corresponding radii into a file
void file_print(int radius, int mass_rad)
{
  ofstream file;
  file.open("fractal_dim_sandbox.csv", ios::app);

  file << radius << "\t" << mass_rad << endl;
  file.close();
}

/*finds the mass M(r) corresponding to a particular radius */
void mass_radius(int x, int y, int radius, int flag[], int mass[], int N)
{
  
  for(int i = -(int)radius/2; i <= (int)radius/2 && x + i >=0 && x + i <= N-1; ++i)
    for(int j = -(int)radius/2; j <= (int)radius/2 && y + j >=0 && y + j <= N-1; ++j)
      {
	if(flag[index(x + i, y + j, N)] == 1)
	  mass[radius]++;
      }

  //  file_print(radius, mass);
  
}



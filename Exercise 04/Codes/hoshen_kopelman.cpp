/**
   Description   : To use HK to find the largest cluster (almost spanning) 
   Author        : Sthavishtha Bhopalam Rajakumar
   Date modified : 28-12-2017
**/

#include<iostream>
#include<cstdlib>
#include<cassert>
#include<fstream>
#include<sys/time.h>
#include "function_list.h"

int *lat, *M, *no_sites;

using namespace std;

//get the time - taken from HPCSE code
double get_wtime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1.0e-6;
}

//returns the index in single array index form
int index(int a, int b, int N)
{
	return (a*N + b);  
}

//returns the actual referencing positive cluster number
int chk_neg_m(int f)
{
	while(M[f] <0)
		f = -M[f];
	
	return f;
}

//checks for any occupied/empty lattice site to the left
int compare_left(int b,int c, int N)
{
  if(lat[index(b,c,N)-1] == 0)
		return 0; //unoccupied
	else
		return 1; //occupied
}

//checks for any occupied/empty lattice site to the right
int compare_top(int b, int c, int N)
{
  if(lat[index(b,c,N)-N] == 0)
		return 0; //unoccupied
	else
		return 1; //occupied
}

//updates M, k and lat arrays if top and bottom sites are empty 
void update_none(int &k,int i,int j, int N)
{
	k++;
	M[k] = 1; //a new cluster
	lat[index(i,j,N)] = k; 
}

//updates M, k and lat arrays if top site is occupied 
void update_sing_top(int i, int j, int N)
{
  lat[index(i,j,N)] = chk_neg_m(lat[index(i,j,N) - N]);
  M[lat[index(i,j,N)]]++;
}	

//updates M, k and lat arrays if left site is occupied
void update_sing_left(int i, int j, int N)
{
  lat[index(i,j,N)] = chk_neg_m(lat[index(i,j,N) - 1]);
  M[lat[index(i,j,N)]]++;
}

//updates M, k and lat arrays if both  top and bottom sites are occupied
void update_both(int i, int j, int N)
{
  int a = chk_neg_m(lat[index(i,j,N) - 1]);
  int b = chk_neg_m(lat[index(i,j,N) - N]);
	
	if(a > b)
	{
	  lat[index(i,j,N)] = b;
		M[b] = M[a] + M[b] + 1;
		M[a] = -b;
	}
	
	else if(a < b)
	{
	  lat[index(i,j,N)] = a;
		M[a] = M[b] + M[a] + 1;
		M[b] = -a;
	}
	
	else
	{
	  lat[index(i,j,N)] = a;
		M[a]++;
	}
}

//initial initialization of M, lat arrays for every step
void initialize(float p, int k, int N)
{
  for(int i = 0; i < N*N; ++i)
    {
      lat[i] = 0;
      M[i] = 0;
      no_sites[i] = 0;
    }
  
  for(int i=0; i < N; i++)
    for(int j=0; j < N; j ++)
      {
	float p_cell = drand48();
	if (p_cell < p)
	  {
	    lat[index(i,j,N)] = 1; //Occupied cells 
	    M[k] = 1; 
	  } 
      }
}
  
//considering the special case of the first row of the cluster
void cluster_first_row(int &k, int N)
{

  for(int j = 0; j < N; ++j)
  {
    if(lat[index(0,j,N)] == 1) //if occupied 
      {
	if(j == 0)
	  {
	    k++;
	    lat[index(0,j,N)] = k;
	    M[k] = 1;
	  }

	else
	  {
	    if (compare_left(0,j,N) == 0)
	      update_none(k,0,j,N);

	    else
	      update_sing_left(0,j,N);
	  }
      }
  }

}

//to find the largest cluster in accordance with the maximum number of sites
int largest_cluster(int k)
{
  int max = 0, cluster_no = 0;
  
  for(int i = 2; i < k; ++i)
    {
      if(M[i] > 0)
	{
	  if(no_sites[M[i]] > max)
	    {
	      max = no_sites[M[i]];
	      cluster_no = i;
	    }
	}
    }
  //  cout << cluster_no << "\t" << max <<endl;
  
  return cluster_no;
}

//initializes flag array to 0 and 1 corresponding to largest or non-largest cluster for a specific site
void flag_find(int cluster_no, int *flag, int N)
{
  int count = 0, ref;
  for(int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      {
	ref = chk_neg_m(lat[index(i,j,N)]);
	if( chk_neg_m(M[ref]) == cluster_no) //correctly referencing the site with negative cluster no
	  {
	    flag[index(i,j,N)] = 1;
	    //	    count++;
	    //	    cout << "1" << "\t" << i << "\t" << j << "\t" << count << endl;
	  }
	else
	  flag[index(i,j,N)] = 0;
      }
}

//The function which uses HK algorithm 
void cluster_size(float p, int flag[], int N)
{
  int f, cluster_no, steps = 0;
  
  lat = new (nothrow) int[N*N];
  M = new (nothrow) int[N*N];
  no_sites = new (nothrow) int [N*N];
  
  assert(lat != NULL);
  assert(M != NULL);
  assert(no_sites != NULL); 

  while(steps < 1) //only once - large number of steps for averaging will be taken care in sandbox.cpp file
    {
      int k = 1;
      unsigned int seed_gen = get_wtime();
      srand48(seed_gen);

      initialize(p, k, N);
      cluster_first_row(k,N);
          
    // Going through the entire loop
      for(int i = 1; i < N; ++i)
	{
	  for(int j = 0; j < N; ++j)
	    {			
	      if(lat[index(i,j,N)] == 1) 
		{
		  if( j == 0)
		    {
		      if(compare_top(i,j,N) == 0)
			update_none(k,i,j,N);

		      else
			update_sing_top(i,j,N);
		    }			

		  else
		    {
		      if(compare_left(i,j,N) == 0 && compare_top(i,j,N) == 0) //both top and left sites are unoccupied
			update_none(k,i,j,N);

		      else if(compare_left(i,j,N) == 0 && compare_top(i,j,N) == 1) //one of the sites - top are occupied
			update_sing_top(i,j,N);

		      else if(compare_left(i,j,N) == 1 && compare_top(i,j,N) == 0) //one of the sites - bottom are occupied
			update_sing_left(i,j,N);

		      else
			update_both(i,j,N);
		    }
		}
	    }
	}

      //computing the number of sites belonging to a cluster
      for(f = 2; f < k; f++)
	{
	  if( M[f] > 0 )
	    no_sites[M[f]]++;
	}

      cluster_no = largest_cluster(k);
      flag_find(cluster_no, flag,N);
     
      steps++;
    }

  delete[] lat;
  delete[] M;
  delete[] no_sites;
}	
		

















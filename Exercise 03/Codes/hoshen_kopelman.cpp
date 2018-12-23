#include<iostream>
#include<cstdlib>
#include<cassert>
#include<fstream>
//#include "latticeview.h"
#include "function_list.h"
#include<omp.h>

int N;
int *lat, *M, *no_sites;

using namespace std;

int ImageWidth = 1000;  //image width
int ImageHeight = 1000; //image height

int index(int a, int b)
{
	return (a*N + b);  
}

int chk_neg_m(int f)
{
	while(M[f] <0)
		f = -M[f];
	
	return f;
}

int compare_left(int b,int c)
{
	if(lat[index(b,c)-1] == 0)
		return 0; //unoccupied
	else
		return 1; //occupied
}

int compare_top(int b, int c)
{
	if(lat[index(b,c)-N] == 0)
		return 0; //unoccupied
	else
		return 1; //occupied
}

void update_none(int &k,int i,int j)
{
	k++;
	M[k] = 1; //a new cluster
	lat[index(i,j)] = k; 
}

void update_sing_top(int i, int j)
{
	lat[index(i,j)] = chk_neg_m(lat[index(i,j) - N]);
	M[lat[index(i,j)]]++;
}	

void update_sing_left(int i, int j)
{
	lat[index(i,j)] = chk_neg_m(lat[index(i,j) - 1]);
	M[lat[index(i,j)]]++;
}

void update_both(int i, int j)
{
	int a = chk_neg_m(lat[index(i,j) - 1]);
	int b = chk_neg_m(lat[index(i,j) - N]);
	
	if(a > b)
	{
		lat[index(i,j)] = b;
		M[b] = M[a] + M[b] + 1;
		M[a] = -b;
	}
	
	else if(a < b)
	{
		lat[index(i,j)] = a;
		M[a] = M[b] + M[a] + 1;
		M[b] = -a;
	}
	
	else
	{
		lat[index(i,j)] = a;
		M[a]++;
	}
}



void cluster_size(float p)
{
  int f;
  N = 500;
  float store_plot[250] = {0.0};

  lat = new (nothrow) int[N*N];
  M = new (nothrow) int[N*N];
  no_sites = new (nothrow) int [N*N];
  
  assert(lat != NULL);
  assert(M != NULL);
  assert(no_sites != NULL); 
  
  char file_name[20];
  sprintf(file_name,"cluster_dist_%f_p.csv",p);

  int time_step = 1, steps = 0;
  ofstream fid, fout;
  fid.open(file_name,ios::app);

  sprintf(file_name,"cluster_dist_%f_p_average.csv",p);
  fout.open(file_name,ios::app);

  	while( steps < 1000)
	  {
	    int k = 1;
        unsigned int seed_gen = omp_get_wtime();
	    
		srand48(seed_gen);
	     #pragma omp parallel
	    {
	      #pragma omp for
	      for(int i =0; i <N*N; i++)
		{
		  lat[i] = 0;
		  M[i] = 0;
		  //		  no_sites[i] = 0;
		}
	    }
	      
	      //	    #pragma omp for collapse(2)
	    for(int i=0; i < N; i++)
	      for(int j=0; j < N; j ++)
		{
		  float p_cell = drand48();
		  if (p_cell < p)
		    {
		      lat[index(i,j)] = 1; //Occupied cells 
		      M[k] = 1; 
		    } 
		}
	    

	    /*Print_lattice(lat, N, N, ImageWidth, ImageHeight, "hk_001.ppm");
	      system("convert hk_001.ppm hk_001.png; rm -f hk_001.ppm");*/

	    // all sites in the first row (top) of the cluster will be studied
	    for(int j = 0; j < N; ++j)
	      {
		if(lat[index(0,j)] == 1) //if occupied 
		  {
		    if(j == 0)
		      {
			k++;
			lat[index(0,j)] = k;
			M[k] = 1;
		      }
			
		    else
		      {
			if (compare_left(0,j) == 0)
			  {
			    k++;
			    lat[index(0,j)] = k;
			    M[k] = 1;
			  }
				
			else
			  {
			    lat[index(0,j)] = lat[index(0,j-1)];
			    M[lat[index(0,j)]]++;
			  }	
		      }
		  }
    	    
		time_step++;
		
		/*sprintf(file_name,"hk_%03d.ppm",time_step);
		  Print_lattice (lat, N, N, ImageWidth, ImageHeight,file_name);
		  sprintf(file_name_png,"hk_%03d.png",time_step);

		  //deleting the ppm file (as its large) and converting it into png file
		  sprintf(cmd,"convert %s %s; rm -f %s",file_name,file_name_png,file_name);
		  system(cmd); */
		
	      }

	    // Going through the entire loop
	    for(int i = 1; i < N; ++i)
	      {
		for(int j = 0; j < N; ++j)
		  {
			
		    if(lat[index(i,j)] == 1) 
		      {
				
			if( j == 0)
			  {
			    if(compare_top(i,j) == 0)
			      update_none(k,i,j);
					
			    else
			      update_sing_top(i,j);
			  }			
					
			else
			  {
				
			    if(compare_left(i,j) == 0 && compare_top(i,j) == 0) //both top and left sites are unoccupied
			      update_none(k,i,j);
					
			    else if(compare_left(i,j) == 0 && compare_top(i,j) == 1) //one of the sites - top are occupied
			      update_sing_top(i,j);
					
			    else if(compare_left(i,j) == 1 && compare_top(i,j) == 0) //one of the sites - bottom are occupied
			      update_sing_left(i,j);
					
			    else
			      {
				update_both(i,j);
			      }
			  }
		      }
			
		    time_step++;
			
		    /*sprintf(file_name,"hk_%03d.ppm",time_step);
		      Print_lattice (lat, N, N, ImageWidth, ImageHeight,file_name);
		      sprintf(file_name_png,"hk_%03d.png",time_step);

		      //deleting the ppm file (as its large) and converting it into png file
		      sprintf(cmd,"convert %s %s; rm -f %s",file_name,file_name_png,file_name);
		      system(cmd); */
		
		  }
	      }

	      for(f = 2; f < k; f++)
		{
		 if( M[f] > 0 )
		 no_sites[M[f]]++;
		}

	      //	      if( steps == 99)
	    for(int i = 2; i < k; i++)
		{
		  int pos = i;
		  if( M[pos] > 0)
		  {
		  int M_val = M[pos];
		  int count = 0;

		  for(int j = 2; j < i; j++)
		    {
		      if(M[j] != M_val)
			 count++;
		    }
		  
		    if(count == (i-2))
		      {
			//fid<<M_val<<"\t"<<(float)no_sites[M_val]/(float)(N*N)<<endl;

			 if(M_val < 220)
			   {
			     if(store_plot[M_val] == 0.0)
			       store_plot[M_val] = (float)no_sites[M_val]/(float)(N*N);
			     else
			       store_plot[M_val] = 0.5*(store_plot[M_val] + (float)no_sites[M_val]/(float)(N*N));
			   }
		      }
		  }
		}

	      steps++;
	//system("convert hk_*.png hk.gif");
	  }
	
	for(int i = 0; i < 250; ++i)
	  if(store_plot[i] != 0.0)
	    fout << i << "\t" << store_plot[i] << endl;

	fid.close();
	fout.close();

	delete[] M;
	delete[] lat;
	delete[] no_sites; 
	
}	
		

















#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>

using namespace std;

double dist_sep(double x1,double x2, double y1,double y2,double z1, double z2)
{
  double calc;
  calc = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)
		      +(z1 - z2)*(z1 - z2));
  return calc;
}

double d_mean_calc(double* a, double* b, double* c,int n)
{
  double d_sum = 0.0;
  for(int i = 0;i < n;i++)
    {
      for(int j = n; j > i; j--)
		{
		  d_sum += dist_sep(a[i],a[j],b[i],b[j],c[i],c[j]);
		}
    }
  return d_sum;
}
	  

//function to check if the new sphere position is separated by a distance of 2R from
// every other sphere
int accept_chk(double*a, double*b, double*c, int count, double radius)
{
  double dist;
  int pos = 0, counter = 0;
  while(pos < count)
  {
	  dist = dist_sep(a[count],a[pos],b[count],b[pos],c[count],c[pos]);
	  if(dist < 2*radius)
	  {
		  counter = 1;
		  break;
	  }
	  pos++ ;
  }
  return counter;
  
	  
/*   while(pos != count)
    {
      dist = dist_sep(a[count],a[pos],b[count],b[pos],c[count],c[pos]);
      if(dist < 2*radius)
	{
	  return 1;
	}
      pos++;
    }
  return 0; */
  
}
  

int main()
{

  int n = 100,count = 0,chk,chk_x,chk_y,chk_z,no = 0 ;
  double L = 10,radius = 1.0, vol_box = L*L*L, vol_sphere, d_mean = 0.;
  double *x,*y,*z,*d_k_mean;
  ofstream file;
  x= (double*)malloc(n*sizeof(double));
  y= (double*)malloc(n*sizeof(double));
  z= (double*)malloc(n*sizeof(double));
  
  file.open("sample_n_100_l10.csv");

  srand48(time(NULL));
  for(int m = 1; m < 5000; m++)
    {
//      cout<<"Computations for m = "<<m<<endl;
      d_k_mean= (double*)malloc(m*sizeof(double));
      while(no < m) 
	{
	  count = 0;
	  while(count < n)
	    {
	      x[count] = L* drand48(); //generating random nos btw 0-L
	      y[count] = L*drand48();
	      z[count] = L*drand48();

	      chk_x = (x[count]>=radius && x[count]<= L-radius); // output 1 - true or 0 - false
	      chk_y = (y[count]>=radius && y[count]<= L-radius);
	      chk_z = (z[count]>=radius && z[count]<=L-radius);

	      //	   cout<<count<<" "<<chk_x<<" "<<x[count]<<" "<<chk_y<<" "<<y[count]<<" "<<chk_z<<" "<<z[count]<<endl;

			if(chk_x !=0 && chk_y!=0 && chk_z!=0) //if true 
			{
			  if(count!= 0)
				{
				  chk = accept_chk(x,y,z,count,radius);
				  if(chk == 0) //non-overlapping spheres
					{
					  count++;
					  //  cout<< count<<endl;
					}
				}
				  else
					count++;
			}
	    }

		vol_sphere = n*4.0*M_PI*pow(radius,3)/3.0; //total volume of all these spheres
      
	  if(vol_sphere < vol_box) //if all these spheres can be accomodated in the cube
	    {
	      d_k_mean[no] = 2*d_mean_calc(x,y,z,n)/(n*(n-1));
	      d_mean += d_k_mean[no];
	      //cout<<"D_k mean of configuration no"<<no<<"= "<<d_k_mean[no]<<endl;
	      no++;
	    }
	}
  
      //cout<<"Average d - <d_mean> = "<<(double) (d_mean/m)<<"for m = "<<m<<endl;
		cout<<m<<"\t"<<(double) (d_mean/m)<<endl;
		file<<m<<"\t"<<(double) (d_mean/m)<<endl;
		free(d_k_mean);
    }
  free(x);
  free(y);
  free(z);
  file.close();
  return 0;
}

 
  
  

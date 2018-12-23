#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double gamm, vx_n, vz_n, vx_new, vz_new, v_mag, alpha,  tim,  delta_t, gravity;

inline void euler()
{
  double v_mag_temp;
  v_mag_temp = vx_n*vx_n + vz_n*vz_n;
  // vx_new = vx_n - delta_t*gamm*sqrt(v_mag_temp)*vx_n;
  // vz_new = vz_n - delta_t*(gravity + gamm*sqrt(v_mag_temp))*vz_n;   	
  vx_n = vx_n - delta_t*gamm*sqrt(v_mag_temp)*vx_n;
  vz_n = vz_n - delta_t*(gravity + gamm*sqrt(v_mag_temp)*vz_n);  
}

inline void pos_update(double *x, double *z)
{

	 *x = *x + delta_t*vx_n;
	 *z = *z + delta_t*vz_n;
	 
}
	
inline void file_print(double x, double z)
{
  ofstream fout;
  char filename[50];
  sprintf(filename, "data_task1_angle%.3lf_vel%.3lf_frict%.3lf.csv",alpha,v_mag, gamm);
	  
  fout.open(filename, ios::app);

  fout << x << "\t" << z << endl;

}

inline void range_max_print(double angle, double friction)
{
  ofstream fout;
  char filename[50];
  sprintf(filename, "range_max%.3lf.csv",v_mag);
  fout.open(filename,ios::app);

  fout << friction << "\t" << angle << endl;
}
    


int main(int argc, char** argv)
{
	//initialization at time step = 0
	
	double x_n = 0., z_n = 0.;
	int iteration = 0;

	v_mag = 80.;
	
#ifdef _TASK1
	alpha = 0.786;
	tim = 0.;
#endif
	
	delta_t = 1e-3;
	gravity = 9.81;
	
#ifdef _TASK1
	gamm = 0.;
	vx_n = v_mag*cos(alpha);
	vz_n = v_mag*sin(alpha);
#endif

#ifdef _TASK1
	do
	{
		tim = tim + delta_t;
		euler();
		pos_update(&x_n, &z_n);		

		iteration++;

		file_print(x_n, z_n);
		
	}while (z_n >= 0.);
	cout << "Velocity components after " << iteration << " iterations" << endl;
	cout << vx_n << " " << vz_n << endl;
#endif

#ifdef _TASK2
	double range_max, alpha_max;
	  
	for(gamm = 0; gamm <= 5; gamm += 0.01)
	  {
	    range_max = 0.;
	    alpha_max = 0.;
	    
	    for(alpha = 0; alpha <= 1.5; alpha += 0.001)
	      {
		x_n = 0., z_n = 0.;
		iteration = 0;
		vx_n = v_mag*cos(alpha);
		vz_n = v_mag*sin(alpha);
		tim = 0.;

		do
		  {
		    tim = tim + delta_t;
		    euler();
		    pos_update(&x_n, &z_n);		
		    iteration++;		
		  }while (z_n >= 0.);

		if(x_n >= range_max)
		  {
		    range_max = x_n;
		    alpha_max = alpha;
		  }
		cout << gamm << "\t" << alpha << "\t" << x_n << "\t" << iteration << endl;
	      }
	    range_max_print(alpha_max, gamm);
	  }
#endif
	
	return 0;
	
}
	
	
	
	

  
	

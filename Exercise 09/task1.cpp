#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>

using namespace std;

double eps = 1e-16;

void user_input(double x0, double y0)
{
        cout << "Enter the value of x0 - to find the maximum of the exponential function\n" << endl;
		cin >> x0;
		cout << "Enter the value of y0 - to find the maximum of the exponential function\n" << endl;
		cin >> y0;
	
}

//evaluates the exponential at x0 and y0
double exp_fn(double x, double y, double x0, double y0)
{
	double val;
	val = exp(-(x - x0)*(x - x0) - (y - y0)*(y - y0));
	//cout << val << endl;
	
	return val;
}

//x- gradient of the given function
double f_x(double x, double y, double x0, double y0)
{

  double value;
  value = -2*exp_fn(x,y,x0,y0)*(x - x0);

  return (value);
}

//y- gradient of the given function
double f_y(double x, double y, double x0, double y0)
{

  double value;
  value = -2*exp_fn(x,y,x0,y0)*(y - y0);

  return (value);
}

//first component in Jacobian
double f_xx(double x, double y, double x0, double y0)
{
		double value;
		value = exp_fn(x,y,x0,y0)*( -2 + 4*(x - x0)*(x - x0));

		return value;
}

//second component in Jacobian
double f_xy(double x, double y, double x0, double y0) //returns the same value as f_yx
{
		double value;
		value = exp_fn(x,y,x0,y0)*(x - x0)*(y - y0)*4;

		return value;
}

//last component in Jacobian
double f_yy(double x, double y, double x0, double y0)
{
		double value;
		value = exp_fn(x,y,x0,y0)*( -2 + 4*(y - y0)*(y - y0));
		
		return value;
}

//equivalent to f_xx, but using finite difference, not analytical
double f_xx_sec(double x, double y, double x0, double y0)
{
  double value, h_x;
  h_x = x*sqrt(eps);
  
  value = (f_x(x + h_x, y, x0, y0) - f_x(x, y, x0, y0))/h_x;

  return value;
}

//equivalent to f_xy, but using finite difference, not analytical
double f_xy_sec(double x, double y, double x0, double y0)
{
  double value, h_y;
  h_y = y*sqrt(eps);
  
  value = (f_x(x, y + h_y, x0, y0) - f_x(x, y, x0, y0))/h_y;

  return value;
}

//equivalent to f_yx, but using finite difference, not analytical
double f_yx_sec(double x, double y, double x0, double y0)
{
  double value, h_x;
  h_x = x*sqrt(eps);
  
  value = (f_y(x + h_x, y, x0, y0) - f_y(x, y, x0, y0))/h_x;

  return value;
}

//equivalent to f_yy, but using finite difference, not analytical
double f_yy_sec(double x, double y, double x0, double y0)
{
  double value, h_y;
  h_y = y*sqrt(eps);
  
  value = (f_y(x, y + h_y, x0, y0) - f_y(x, y, x0, y0))/h_y;

  return value;
}

//determinant of the matrix 
double det(double a, double b, double c, double d)
{
	double det_val;
	det_val = (a*d - b*c);
	return det_val;

}


int main(int argv, char** argc)
{

	int user = 0, iter = 1; //user = 0 determines the default x0 and y0 values to be used. 
	//Else, for user to input these values, equate user = 1

	int secant_met = 1; //1 causes secant method of Jacobian computation. 0 uses the conventional way
	
	double x0 = 3, y0 = 4, x_old =2.6, y_old =3.7, error = 1., magnitude; //x0, y0 - guess  values
	
	double x_new, y_new, mult_x, mult_y, lambda = 1.0; // lambda refers to the relaxation factor

	ofstream fout;
	fout.open("convergence_data_secant.dat");
	fout << "Error" << "\t" << "X_updated" << "\t" << "Y_updated" << "\t" << "Iteration" << endl;
       

	if (user == 1)
	  user_input(x0,y0);
	
	while(error > 1e-5)
	{

	  if (secant_met ==1) //using the secant way of evaluating Jacobian - Finite differences
	    {
	      mult_x = f_x(x_old, y_old, x0, y0)*f_yy_sec(x_old, y_old, x0, y0) - f_y(x_old, y_old, x0, y0)*f_xy_sec(x_old, y_old, x0, y0);
	      mult_y = f_y(x_old, y_old, x0, y0)*f_xx_sec(x_old, y_old, x0, y0) - f_x(x_old, y_old, x0, y0)*f_yx_sec(x_old, y_old, x0, y0);
	    
		  x_new = x_old - lambda*mult_x/det(f_xx_sec(x_old, y_old, x0, y0), f_xy_sec(x_old, y_old, x0, y0), f_yx_sec(x_old, y_old, x0, y0), f_yy_sec(x_old, y_old, x0, y0)); //Generalized newton's method
		  y_new = y_old - lambda*mult_y/det(f_xx_sec(x_old, y_old, x0, y0), f_xy_sec(x_old, y_old, x0, y0), f_yx_sec(x_old, y_old, x0, y0), f_yy_sec(x_old, y_old, x0, y0));
	    }
	      
	  else // implementing conventional way of computing Jacobian
	    {
	      mult_x = f_x(x_old, y_old, x0, y0)*f_yy(x_old, y_old, x0, y0) - f_y(x_old, y_old, x0, y0)*f_xy(x_old, y_old, x0, y0);
	      mult_y = f_y(x_old, y_old, x0, y0)*f_xx(x_old, y_old, x0, y0) - f_x(x_old, y_old, x0, y0)*f_xy(x_old, y_old, x0, y0);
		  
		  cout << setprecision(7) << f_xx(x_old, y_old, x0, y0) << "\t" << setprecision(7) << f_xy(x_old, y_old, x0, y0) << "\t" << setprecision(7)<< f_yy(x_old, y_old, x0, y0) << endl;
	    
			x_new = x_old - lambda*mult_x/det(f_xx(x_old, y_old, x0, y0), f_xy(x_old, y_old, x0, y0), f_xy(x_old, y_old, x0, y0), f_yy(x_old, y_old, x0, y0)); //Generalized newton's method
			y_new = y_old - lambda*mult_y/det(f_xx(x_old, y_old, x0, y0), f_xy(x_old, y_old, x0, y0), f_xy(x_old, y_old, x0, y0), f_yy(x_old, y_old, x0, y0));
	    }
		
		magnitude = fabs( (x_new - x_old)*(x_new - x_old) + (y_new - y_old)*(y_new - y_old)); 
		error = sqrt(magnitude); //calculating the error for convergence 

		x_old = x_new;
		y_old = y_new;
		
		cout << fixed;
		cout << "Error = " <<  error << "\t" << "Iteration" << "\t" <<  iter << endl << "X updated" << "\t" << x_new << "\t" << "Y_updated" << "\t" << y_new << endl;
		fout << fixed;
		fout << error << "\t" << x_new << "\t" << y_new << "\t" << iter << endl;
		  
		iter++;
	}
		

	fout.close();
	return 0;
}
	
	
	
	
	
	

/*
Uniform distribution of random points in the circle
Author : Sthavishtha Bhopalam Rajakumar, MSc in Mechanical Eng.
Code updated on : 02-10-2017
*/

#include<iostream>
#include<fstream>
#include<cmath>

# define M_PI  3.14159265358979323846 /* pi */

using namespace std;

int main()
{
	int r_o,r_o_user,theta_o,theta_o_user,c1,c2,p,r_n,theta_n;	
	float x,y, radius, theta;
	ofstream myfile ("task2_fig1.dat");
	cout<<"For the random radii :"<<endl;
	cout<<"Enter the input seed r_o - Must be a positive integer\n";
	cin>>r_o_user;
	cout<<"For the random theta :"<<endl;
	cout<<"Enter the input seed theta_o - Must be a positive integer\n";
	cin>>theta_o_user;
	cout<<"Enter the value of c1 - Must be a positive integer\n";
	cin>>c1;
	cout<<"Enter the value of c2 - Must be a positive integer\n";
	cin>>c2;
	cout<<"Enter the value of p - Must be a positive integer\n";
	cin>>p;
	r_o = r_o_user;
	theta_o = theta_o_user;
	radius = sqrt((float)r_o/p);
	theta = (float) 2*M_PI*theta_o/p;
	x = radius*cos((float)theta);
	y = radius*sin((float)theta);
	myfile<<x<<"\t"<<y<<endl;
	do
	{	
		r_n = (c1*r_o)%p;
		theta_n = (c2*theta_o)%p;
		radius = sqrt((float)r_n/p);
		theta = (float) 2*M_PI*theta_n/p;
		x = radius*cos((float)theta);
		y = radius*sin((float)theta);
		myfile<<x<<"\t"<<y<<endl;
		cout<<x<<"\t"<<y<<"\t"<<r_n<<"\t"<<theta_n<<endl;
		r_o = r_n;
		theta_o = theta_n;
		
	}while(r_o < p && r_o!= r_o_user && theta_o < p && theta_o!= theta_o_user);

	return 0;
	
}

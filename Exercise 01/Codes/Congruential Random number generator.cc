/*
Congruential Random number generator
Author : Sthavishtha Bhopalam Rajakumar, MSc in Mechanical Eng.
Code updated on : 01-10-2017
*/

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	int x_o_user,x_o,c,p,x_n,count=1; //c,p and x_o are taken to be positive integers
	ofstream myfile ("task1_fig1.dat");
	cout<<"Enter the input seed x_o - Must be a positive integer\n";
	cin>>x_o_user;
	cout<<"Enter the value of c - Must be a positive integer\n";
	cin>>c;
	cout<<"Enter the value of p - Must be a positive integer\n";
	cin>>p;
	
	//check if p is a Merseinne no - for the maximal period
	
	x_o = x_o_user;
	cout<<x_o<<endl;
	//myfile.open();
	myfile<<count<<"\t"<<x_o<<endl;
	do
	{	
		count++;
		x_n = (c*x_o)%p;
		myfile<<count<<"\t"<<x_n<<endl;
		cout<<x_n<<endl;
		x_o = x_n;
		
	}while(x_o < p && x_o!= x_o_user);
	myfile.close();
		
	return 0;
	
}


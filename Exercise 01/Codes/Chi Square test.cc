/*
chi-square test
Author : Sthavishtha Bhopalam Rajakumar, MSc in Mechanical Eng.
Code updated on : 02-10-2017
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main()
{
	int x_o_user,x_o,c,p,x_n,bins = 8,count_tot=1; //c,p and x_o are taken to be positive integers
	float z[200]={0.0},chi_sq = 0.0,temp,temp_o;
	int count[200] = {0};
	cout<<"Enter the input seed x_o - Must be a positive integer\n";
	cin>>x_o_user;
	cout<<"Enter the value of c - Must be a positive integer\n";
	cin>>c;
	cout<<"Enter the value of p - Must be a positive integer\n";
	cin>>p;
	x_o = x_o_user;
	z[0] = (float) x_o/p;
	temp_o = z[0];
	do
	{	
		x_n = (c*x_o)%p;
		z[count_tot] = (float) x_n/p;
		temp = z[count_tot];
		if(temp <  0.125 || (temp_o <  0.125 && count_tot==1))
			count[0]++;
		else if(temp <0.25 || (temp_o <  0.25 && count_tot==1))
			count[1]++;
		else if(temp < 0.375 || (temp_o < 0.375 && count_tot==1))
			count[2]++;
		else if(temp <  0.5 || (temp_o <  0.5 && count_tot==1))
			count[3]++;
		else if(temp <  0.625 || (temp_o <  0.625 && count_tot==1))
			count[4]++;
		else if(temp <  0.75 || (temp_o <  0.75 && count_tot==1))
			count[5]++;
		else if(temp <  0.875 || (temp_o <  0.875 && count_tot==1))
			count[6]++;
		else 
			count[7]++;	
		x_o = x_n;
		count_tot++;
		
	}while(x_o < p && x_o!= x_o_user);
	
	for(int i=0;i<bins;i++)
		chi_sq  += ((float) count[i] - ((float) (count_tot/bins)))*((float) count[i] - ((float) (count_tot/bins)))/((float)count_tot/bins);
	
	cout<<"the value of chi-square for this sequence is "<<chi_sq;
	return 0;
		
}

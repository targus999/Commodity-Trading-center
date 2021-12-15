#include<iostream>
using namespace std;

void multiplication(int a,int b)
{
	int c=a*b;
	cout<<"product="<<c;
}

void subtraction(int a,int b)
{
 int c=0,a=10,b=5;
 c=a-b;
 cout<<"subtracting "<<a<< "from "<<b" is : "<<c;
}

int main()
{
int a=4,b=6;
multiplication(a,b);
subtraction(a,b);  
return 0;
}




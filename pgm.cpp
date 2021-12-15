#include<iostream>
using namespace std;

void add(int a,int b){
  int sum=a+b;
  cout<<"Addition "<<sum<<endl;
}

void multiplication(int a,int b)
{
	int c=a*b;
	cout<<"product="<<c;
}

void subtraction(int a,int b)
{
 int c=a-b;
 cout<<"subtracting "<<a<< "from "<<b<<" is : "<<c;
}

void divide(int a,int b){
	int result;
	result=a/b;
	cout<<"Result = "<<result<<endl;
}

int main()
{
int a=4,b=6;
multiplication(a,b);
subtraction(a,b);  
add(a,b);
divide(a,b);
  
return 0;

}




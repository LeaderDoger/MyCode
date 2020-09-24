#include <stdio.h>
#include <math.h>

double Simpson(double f(double x),double a,double b,int n)
{
	const double h=(b-a)/n;
	double S=f(a)-f(b);
	int i;
	for(i = 1;i < n;i +=2)S+=4*f(a+i*h);
	for(i = 1;i < n;i +=2)S+=2*f(a+i*h);
	return S*h/3.0;
}

double fun(double x)
{
	return sin(x);
}


void main()
{
	double a,b;
	int n;
	double Simpson(double f(double x),double a,double b,int n);
	scanf("%lf %lf",&a,&b);
	scanf("%d",&n);
	printf("%lf",Simpson(fun,a,b,n));
}
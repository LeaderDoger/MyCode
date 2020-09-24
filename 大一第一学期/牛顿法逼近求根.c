#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
	double n;
	long double result,left,right,x;
	printf("用牛顿法逼近求x3-4x+1=0的根\n");
	printf("请输入精准度：");
	scanf_s("%lf",&n);
	left=0;right=1;
	printf("f(0)=1\n");
	printf("f(1)=-1\n");
	result=1;
	while(fabs(result)>n)
	{
		x=(left+right)/2;
		result=pow(x,3)-4*x+1;
		if(result<0)right=x;
		else left=x;
		printf("f(%lf)=%lf\n",x,result);
	}
	system("pause");
}

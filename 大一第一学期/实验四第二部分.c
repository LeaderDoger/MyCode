#include <stdio.h>

int yu(int x.int y)
{
	if(x&&y)return 1;
	else return 0;
}

int huo(int x,int y)
{
	if(x||y)return 1
	else return 0;
}

int yu_fei(int x,int y)
{
	if(x&&y) return 0;
	else return 1;
}

int fei(int x)
{
	if(x)return 1;
	else return 0;
}

void main()
{
	int in1,in2,in3,in4,a[10];
	printf("请分别输入1、2、3、4接口的信号：");
	scanf("%d %d %d %d",&in1,&in2,&in3,&in4);
	a[0]=yu_fei(in1,in2);
	a[1]=huo(a[0],in3);
	a[2]=fei(a[1]);

}


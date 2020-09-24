#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define N 100

void main()
{
	void calc_sel(int sel);
	int num;
	while(1){
		/*显示菜单*/
		printf("                   菜单功能\n");
		printf("------------------------------------------------\n");
		printf("        1-矩阵加法             2-矩阵减法       \n");
		printf("        3-矩阵乘法             4-矩阵幂运算     \n");
		printf("        5-矩阵转置             6-矩阵行列式     \n");
		printf("                     0-退出                     \n");
		printf("------------------------------------------------\n");
		/*选择菜单*/
		printf("请选择你要进行的运算；");
		scanf_s("%d",&num);
		/*退出*/
		if (num>0&&num<=6)
		{
			calc_sel(num);
		}
		else if(num==0){
			printf("欢迎下次使用");
			break;
		}
		else printf("\n选择错误，请重新选择！\n\n");
	}
}

void calc_sel(int sel)
{
	int i,j;
	void matrix_sum(int i,int j);
	void matrix_sub(int i,int j);
	void matrix_mul(int i,int j);
	void mat_tra(int i,int j);
	void mat_pow(int n,int x);
	void matrix_det(int m);
	void inverse_mat(int n);

	switch (sel){
	case 1://矩阵加法
		printf("请输入矩阵的行与列（用空格隔开）：");
		scanf("%d %d",&i,&j);
		matrix_sum(i,j);
		break;
	case 2://矩阵减法
		printf("请输入矩阵的行与列（用空格隔开）：");
		scanf("%d %d",&i,&j);
		matrix_sub(i,j);
		break;
	case 3://矩阵乘法
		printf("请输入第一个矩阵的行与列（用空格隔开）：");
		scanf("%d %d",&i,&j);
		matrix_mul(i,j);
		break;
	case 4://矩阵幂运算
		printf("请输入矩阵的阶级和幂数（用空格隔开）：");
		scanf("%d %d",&i,&j);
		mat_pow(i,j);
		break;
	case 5://矩阵转置
		printf("请输入矩阵的行与列（用空格隔开）：");
		scanf("%d %d",&i,&j);
		mat_tra(i,j);
		break;
	case 6://矩阵行列式
		printf("请输入方阵的阶级：\n");
		scanf("%d",&i);
		matrix_det(i);
		break;
	case 7://逆矩阵运算
		printf("请输入方阵的阶级：\n");
		scanf("%d", &i);
		inverse_mat(i);
		break;
	}
}

void matrix_sum(int i,int j)
{
	int n,m;
	void matrix_dis(int (*p)[N],int i,int j);
	int a[N][N],b[N][N],c[N][N];
	
	printf("请输入第一个矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&a[n][m]);
	printf("请输入第二个矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&b[n][m]);
	printf("您输入的第一个矩阵\n");
	matrix_dis(a,i,j);
	printf("您输入的第二个矩阵\n");
	matrix_dis(a,i,j);
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			c[n][m]=a[n][m]+b[n][m];
	printf("相加得到的结果为：\n");
	for(n=0;n<i;n++){
		for(m=0;m<j;m++){
			printf("%d",c[n][m]);
			if(m!=j-1)printf(" ");		
		}
		printf("\n\n");
	}
}

void matrix_sub(int i,int j)
{
	int n,m;
	void matrix_dis(int (*p)[N],int i,int j);
	int a[N][N],b[N][N],c[N][N];
	printf("请输入第一个矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&a[n][m]);
	printf("请输入第二个矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&b[n][m]);
	printf("您输入的第一个矩阵\n");
	matrix_dis(a,i,j);
	printf("您输入的第二个矩阵\n");
	matrix_dis(a,i,j);
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			c[n][m]=a[n][m]-b[n][m];
	printf("相加得到的结果为：\n");
	for(n=0;n<i;n++){
		for(m=0;m<j;m++){
			printf("%d",c[n][m]);
			if(m!=j-1)printf(" ");		
		}
		printf("\n\n");
	}
}

void matrix_mul(int i,int j)
{
	int n,m,k;
	int j2;
	void matrix_dis(int (*p)[N],int i,int j);
	int a[N][N],b[N][N],c[N][N]={0};
	
	
	printf("请输入第二个矩阵的列");
	scanf("%d", &j2);
	
	printf("请输入第一个矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&a[n][m]);
	printf("请输入第二个矩阵\n");
	for(n=0;n<j;n++)
		for(m=0;m<j2;m++)
			scanf("%d",&b[n][m]);
	printf("您输入的第一个矩阵\n");
	matrix_dis(a,i,j);
	printf("您输入的第二个矩阵\n");
	matrix_dis(b,j,j2);
	for(n=0;n<i;n++)
	{
		for(m=0;m<j2;m++)
		{
			for(k=0;k<j;k++)
				c[n][m]+=a[n][k]*b[k][m];
		}
	}
	printf("相乘得到的结果为：\n");
	for(n=0;n<i;n++){
		for(m=0;m<j2;m++){
			printf("%d",c[n][m]);
			if(m!=j-1)printf(" ");		
		}
		printf("\n\n");
	}
}

void mat_pow(int n,int x)
{
	int p[N][N],b[N][N],c[N][N];
	int i,j,q,k;
	void matrix_dis(int (*p)[N],int i,int j);
	printf("请输入%d阶的方阵：\n",n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&p[i][j]);
	printf("您输入的%d阶方阵为\n",n);
	matrix_dis(p,n,n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			b[i][j]=p[i][j];
	if(x==0){
		for(i=0;i<n;i++)
			for(j=0;j<n;j++){
				if(i==j)p[i][j]=1;
				else p[i][j]=0;
			}
	}
	else 
	{
		for(q=1;q<x;q++)
		{
			memset(c,0,sizeof(c));
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					for(k=0;k<n;k++)
						c[i][j]+=p[i][k]*b[k][j];
				}
			}
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					p[i][j]=c[i][j];
		}
	}
	printf("计算的结果为\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++){
			printf("%d",p[i][j]);
			if(j!=n-1)printf(" ");
		}
		printf("\n");
	}
}

void mat_tra(int i,int j)
{
	int n,m;
	void matrix_dis(int (*p)[N],int i,int j);
	int a[N][N],b[N][N];
	printf("请输入矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			scanf("%d",&a[n][m]);
	printf("您输入的矩阵\n");
	matrix_dis(a,i,j);
	printf("转置后的矩阵\n");
	for(n=0;n<i;n++)
		for(m=0;m<j;m++)
			b[m][n]=a[n][m];
	matrix_dis(b,j,i);
}

void matrix_dis(int (*p)[N],int i,int j)
{
	int n,m;
	for(n=0;n<i;n++){
		for(m=0;m<j;m++){
			printf("%3d",p[n][m]);
			if(m!=j-1)printf(" ");		
		}
		printf("\n");
	}
}

void matrix_det(int m)
{
	int matrixDet(int m,int** a);
	int** inputmatrix(int m);
	int **A,sum;
	A=inputmatrix(m);
	sum=matrixDet(m,A);
	printf("您输入的矩阵的行列式为：%d\n",sum);
}

int matrixDet(int m,int** a)
{	
	int k, j, i;	//预分配二维数组内存	
	int** b = (int**)malloc(sizeof(int*)*m);
	int sum = 0, offset = 0;
	for (i = 0; i < m; i++)	
	{		
		b[i] = (int*)malloc(sizeof(int)*m);	
	}
	if(m==1)return a[0][0];
	for (k = 0; k < m; k++)
	{
		for (i = 0; i < m - 1; i++)		
		{	
			if (i < k)offset = 0;
			else	offset = 1;			
			for (j = 0; j < m - 1; j++)				
				b[i][j] = a[i + offset][j + 1];		
		}	
		sum = sum + a[k][0] * pow(-1.0, k + 0)*matrixDet(m - 1, b);	
	}	
	return sum;
}

int** inputmatrix(int m)//输入正矩阵
{
	int i,j;
	int ** a=(int **)malloc(sizeof(int*)*m);
	for(i=0;i<m;i++)
		a[i]=(int*)malloc(sizeof(int)*m);
	printf("输入矩阵的所有元素：\n");
	for(i=0;i<m;i++)
		for(j=0;j<m;j++)
			scanf("%d",&a[i][j]);
	printf("您输入的矩阵\n");
	for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			printf("%3d",a[i][j]);
			if(j!=m-1)printf(" ");		
		}
		printf("\n");
	}
	return a;
}

void inverse_mat(int n)
{





}
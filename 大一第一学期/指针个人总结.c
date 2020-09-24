#include<stdio.h>
void main()
{
	int array[4][5]={0};
	int i,j,k=0;
	for(i = 0;i < 4; i++)
	{
		for(j = 0;j < 5; j++){
			array[i][j]=k++;
		}

	}

	printf("*(array+1):%p\n",*(array+1));
	printf("array+1:%p\n",array+1);
	printf("array[1]::%p\n",array[1]);
	printf("&array[1][0]:%p\n",&array[1][0]);
	printf("array[1][0]:%p\n",array[1][0]);
	printf("array[1]+2:%p\n",array[1]+2);
	printf("&array[1]+2:%p\n",&array[1]+2);
	printf("*(array[1]+2):%p\n",*(array[1]+2));
	printf("array[1][2]:%p\n",array[1][2]);
	printf("指针的所指按照先行后列的原则\n");
	printf("取值运算符取一组指针时，显示第一个指针的位置\n");
	printf("取值运算符取一个指针时，显示所取地址的变量的值\n");
	printf("若指针没有选择到一个地址的地步(且用中括号括起来)\n显示的是所指的数组的第一个的地址或者所指的数的地址\n");
	printf("所取列则为列的第一个地址，行则为行的第一个地址\n");
}
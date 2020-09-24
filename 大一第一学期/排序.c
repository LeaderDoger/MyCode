#include "base.h"



typedef int ElementType;

void ShellSort(ElementType A[], int N,int* count)
{ /* 希尔排序 - 用Sedgewick增量序列 */
	int Si, D, P, i;
	ElementType Tmp;
	/* 这里只列出一小部分增量 */
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1 };

	(*count)=0;

	for (Si = 0; Sedgewick[Si] >= N; Si++)
		; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */

	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si],(*count)++)
		for (P = D; P < N; P++) { /* 插入排序*/
			Tmp = A[P];
			for (i = P; i >= D && A[i - D] > Tmp; i -= D)
				A[i] = A[i - D];
			A[i] = Tmp;
		}
}

int* Create_randnum(int count, int min, int max)
{//随机生成一个数量为count，范围在min到max之间的数组
	int* nums = (int*)malloc(sizeof(int) * count);
	int i;
	for (i = 0; i < count; i++)
		nums[i] = rand(time(0)) % (max - min) + min;
	return nums;
}

void Print_nums(int* nums, int count)
{//将数组的前count个数打印，并释放数组
	int i;
	for (i = 0; i < count; i++) {
		printf("%-5d", nums[i]);
		if (i % 10 == 9)printf("\n");
		else printf(",");
	}
	free(nums);
}

/* 快速排序 */
void Swap(ElementType* a, ElementType* b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
	/* 此时A[Left] <= A[Center] <= A[Right] */
	Swap(&A[Center], &A[Right - 1]); /* 将基准Pivot藏到右边*/
	/* 只需要考虑A[Left+1] … A[Right-2] */
	return  A[Right - 1];  /* 返回基准Pivot */
}

void InsertionSort(ElementType A[], int count)
{
	int  i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < count-1; j++)
			if (A[j] > A[j + 1]) {
				Swap(A + j, A + (j + 1));
			}
}

void Qsort(ElementType A[], int Left, int Right,int* count)
{ /* 核心递归函数 */
	int Pivot, Cutoff=5, Low, High;
	(*count)++;

	if (Cutoff <= Right - Left) { /* 如果序列元素充分多，进入快排 */
		Pivot = Median3(A, Left, Right); /* 选基准 */
		Low = Left; High = Right - 1;
		while (1) { /*将序列中比基准小的移到基准左边，大的移到右边*/
			while (A[++Low] < Pivot);
			while (A[--High] > Pivot);
			if (Low < High) Swap(&A[Low], &A[High]);
			else break;
		}
		Swap(&A[Low], &A[Right - 1]);   /* 将基准换到正确的位置 */
		Qsort(A, Left, Low - 1,count);    /* 递归解决左边 */
		Qsort(A, Low + 1, Right,count);   /* 递归解决右边 */
	}
	else InsertionSort(A + Left, Right - Left + 1); /* 元素太少，用简单排序 */
}

void QuickSort(ElementType A[], int N,int* count)
{ /* 统一接口 */
	(*count)=0;
	Qsort(A, 0, N - 1,count);
}

//堆排序
void PercDown(ElementType A[], int p, int N)
{ /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
	/* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
	int Parent, Child;
	ElementType X;

	X = A[p]; /* 取出根结点存放的值 */
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			Child++;  /* Child指向左右子结点的较大者 */
		if (X >= A[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}

void HeapSort(ElementType A[], int N,int* count)
{ /* 堆排序 */
	int i;
	*(count)=0;
	for (i = N / 2 - 1; i >= 0; i--)/* 建立最大堆 */
		PercDown(A, i, N);

	for (i = N - 1; i > 0; i--,(*count)++) {
		/* 删除最大堆顶 */
		Swap(&A[0], &A[i]); 
		PercDown(A, 0, i);
	}
}






int main()
{
	int* nums;
	int count=0;

	printf("希尔排序\n");
	nums = Create_randnum(100, 200, 1000);

	ShellSort(nums, 100,&count);
	printf("执行希尔排序的次数为：%d\n",count);
	Print_nums(nums, 100);
	printf("\n");

	printf("快速排序\n");
	nums = Create_randnum(200, 200, 10000);

	QuickSort(nums, 200,&count);
	printf("执行快速排序的次数为：%d\n",count);
	Print_nums(nums, 200);
	printf("\n");

	printf("堆排序\n");
	nums = Create_randnum(500, 200, 100000);

	HeapSort(nums, 500,&count);
	printf("执行堆排序的次数为：%d\n",count);
	Print_nums(nums, 500);


}
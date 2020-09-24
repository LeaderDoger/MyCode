#include <stdio.h>
#include <malloc.h>

#define false 0;
#define true 1;

typedef int Position;
typedef char ElementType;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;

//创建(初始化)队列Q
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

//判断队列Q是否为空
int IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
//判断队列Q是否为满
int IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

//入队
int AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

//出队
ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) { 
        printf("队列空");
        return ' ';
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}

//输出队列中元素的个数
int countQ( Queue Q)
{
	return (Q->Rear+Q->MaxSize-Q->Front)%Q->MaxSize;
}

int main()
{
	int i;
	char a;
	Queue Q;
	Q=CreateQueue(20);
	printf("输入若干元素（不少于10个）入队\n");
	for(i=0;i<10;i++){
		scanf("%c",&a);
		if(!AddQ(Q,a))return 1;
	}
	getchar();//提取回车
	a=DeleteQ(Q);
	printf("%c\n",a);
	printf("%d\n",countQ(Q));
	for(i=0;i<4;i++){
		scanf("%c",&a);
		AddQ(Q,a);
	}
	while (!IsEmpty(Q))
	{
		a=DeleteQ(Q);
		printf("%c",a);
	}
	printf("\n");
	return 0;
}



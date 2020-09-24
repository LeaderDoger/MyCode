#include "base.h"


typedef struct TNode *Position1;
typedef Position1 BinTree; /* 二叉树类型 */
typedef  char ElementType1;
struct TNode{ /* 树结点定义 */
    ElementType1 Data; /* 结点数据 */
    BinTree Left;     /* 指向左子树 */
    BinTree Right;    /* 指向右子树 */
};

typedef	 BinTree ElementType2;
typedef struct SNode *PtrToSNode;
struct SNode {
    ElementType2 Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

typedef struct Node *PtrToNode;
struct Node { /* 队列中的结点 */
    ElementType2 Data;
    PtrToNode Next;
};
typedef PtrToNode Position2;
 
struct QNode {
    Position2 Front, Rear;  /* 队列的头、尾指针 */

};
typedef struct QNode *Queue;

//堆栈
Stack CreateStack( ) 
{ /* 构建一个堆栈的头结点，返回该结点指针 */
    Stack S;
 
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
 
int IsEmpty ( Stack S )
{ /* 判断堆栈S是否为空，若是返回true；否则返回false */
    return ( S->Next == NULL );
}
 
int Push( Stack S, ElementType2 X )
{ /* 将元素X压入堆栈S */
    PtrToSNode TmpCell;
 
    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return TRUE;
}
 
ElementType2 Pop( Stack S )  
{ /* 删除并返回堆栈S的栈顶元素 */
    PtrToSNode FirstCell;
    ElementType2 TopElem;
 
    if( IsEmpty(S) ) {
        printf("堆栈空"); 
        return ERROR;
    }
    else {
        FirstCell = S->Next; 
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}

//树
void CreateTree(BinTree *T)                          
{           
    char ch;
    scanf("%c",&ch);

    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        (*T)=(BinTree)malloc(sizeof(struct TNode));
        if(!(*T))exit(0);
        (*T)->Data=ch;
        CreateTree(&((*T)->Left));
        CreateTree(&((*T)->Right));
    }
}

//先序非递归遍历算法
void PreorderTraversal(BinTree BT)
{
	BinTree T=BT;
	Stack S =CreateStack();
	while (T || !IsEmpty(S)){
		while (T){ //一直向左并将沿途的节点压入堆栈
			Push(S,T);
			printf("%c ", T->Data);//访问打印节点
			T=T->Left;
		}
		if(!IsEmpty(S)){
			T = Pop(S);//节点弹出堆栈
			T = T->Right;//转向右节点
		}

	}
}

//中序非递归遍历算法
void InorderTraversal(BinTree BT)
{
	BinTree T=BT;
	Stack S =CreateStack();
	while (T || !IsEmpty(S)){
		while (T){ //一直向左并将沿途的节点压入堆栈
			Push(S,T);
			T=T->Left;
		}
		if(!IsEmpty(S)){
			T = Pop(S);//节点弹出堆栈
			printf("%c ", T->Data);//访问打印节点
			T = T->Right;//转向右节点
		}

	}
}

//二叉树后序遍历
void PostOrderTraversal(BinTree BT)
{
	if(BT){
		PostOrderTraversal(BT->Left);
		PostOrderTraversal(BT->Right);
		printf("%c ",BT->Data);
	}

}

//层序遍历
void LevelorderTraversal(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* 创建空队列Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		printf("%c ", T->Data); /* 访问取出队列的结点 */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}
//层序遍历叶节点
void LevelorderTraversalleaves(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* 创建空队列Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		if(!T->Left && !T->Right)
		printf("%c ", T->Data); /* 访问取出队列的结点 */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}

//层序遍历非叶节点
void LevelorderTraversalNotleaves(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* 创建空队列Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		if(!(!T->Left && !T->Right))
		printf("%c ", T->Data); /* 访问取出队列的结点 */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}
int Max ( int a, int b )
{
    return a > b ? a : b;
}

//计算树的深度
int DeepthTree(BinTree T)
{
	if(!T->Left && !T->Right)
		return 1;
	if(!T->Left && T->Right)
		return DeepthTree(T->Right)+1;
	if(!T->Right && T->Left)
		return DeepthTree(T->Left)+1;
	if (T->Left && T->Right)
		return Max(DeepthTree(T->Left),DeepthTree(T->Right))+1;
	return -1;
}


//队列
Queue CreatQueue()
{
	Queue Q;
	Q=(Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

Status Isempty( Queue Q )
{
    return ( Q->Front == NULL);
}

ElementType2 DeleteQ( Queue Q )
{
    Position2 FrontCell; 
    ElementType2 FrontElem;
     
    if  ( Isempty(Q) ) {
        printf("队列空");
        return NULL;
    }
    else {
        FrontCell = Q->Front;
        if ( Q->Front == Q->Rear ) /* 若队列只有一个元素 */
            Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
        else                     
            Q->Front = Q->Front->Next;
        FrontElem = FrontCell->Data;
 
        free( FrontCell );  /* 释放被删除结点空间  */
        return  FrontElem;
    }
}

Status AddQ(Queue Q,ElementType2 X)
{
	Position2 RearCell;
	RearCell=(Position2)malloc(sizeof(struct QNode));
	RearCell->Data = X;
	if(!Q->Front && !Q->Rear)//没有元素
	Q->Front = Q->Rear = RearCell;
	else {
		Q->Rear->Next= RearCell;
		Q->Rear = Q->Rear->Next;
	}
	return TRUE;

     
    
}








int main()
{
	BinTree T;
	printf("请按前序输入数据\n");
	CreateTree(&T);
	printf("按前序遍历该树\n");
	PreorderTraversal(T);
	printf("\n");
	printf("按中序遍历该树\n");
	InorderTraversal(T);
	printf("\n");
	printf("按后序遍历该树\n");
	PostOrderTraversal(T);
	printf("\n");
	printf("按层次遍历该树\n");
	LevelorderTraversal(T);
	printf("\n");
	printf("该树的深度为:");
	printf("%d",DeepthTree(T));
	printf("\n");
	printf("该树的叶节点为:");
	LevelorderTraversalleaves(T);
	printf("\n");
	printf("该树的非叶节点为:");
	LevelorderTraversalNotleaves(T);
	printf("\n");
	return 0;
}



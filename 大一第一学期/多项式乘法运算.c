#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct PolyNode {
	int coef;	//系数
	int expon;	//指数
	struct PolyNode *link;	//指向下一个节点的指针
};
typedef struct PolyNode* Polynomial;

int Compare(int a,int b)
{
	if(a>b)return 1;
	if(b>a)return -1;
	return 0;
}

void Attach(int c,int e,Polynomial *pRear)
{	//由于在本函数中需要改变当前结果表达式尾项指针的值
	//所以函数传递进来的是节点指针的地址，*pRear指向尾项
	Polynomial p;

	p=(Polynomial)malloc(sizeof(struct PolyNode));
	p->coef =c;
	p->expon = e;
	p->link=NULL;
	//将p指向的新节点插入到当前结果表达式的尾项的后面
	(*pRear)->link = p;
	(*pRear)=p;//迭代
}
//生成没有空头结点的多项式链表
Polynomial ReadPoly()
{
	int N,c,e;
	Polynomial Rear,P,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));//链表空节点
	P ->link = NULL;
	Rear = P;
	printf("请输入多项式的项数");
	scanf("%d",&N);
	if(N<=0)return;
	while(N--){
		printf("请输入系数和指数");
		scanf("%d %d",&c,&e);
		Attach(c,e, &Rear);
	}
	t = P;P = P->link;free(t);//删除临时头结点
	return P;
}

Polynomial PolyAdd (Polynomial p1,Polynomial p2)
{
	Polynomial front,rear,temp;
	int sum;
	rear=(Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;//由front记录结果多项式链表头结点
	while(p1&&p2)
		switch(Compare(p1->expon,p2->expon)){
		case 1:
			Attach(p1->coef,p1->expon,&rear);
			p1=p1->link;
			break;
		case -1:
			Attach(p2->coef,p2->expon,&rear);
			p2=p2->link;
			break;
		case 0:
			sum =p1->coef+p2->coef;
			if(sum)Attach(sum,p1->expon,&rear);
			p1=p1->link;
			p2=p2->link;
			break;
	}
	//将未处理完的另一个多项式的所有节点一次复制到结果多项式中去
	for(;p1;p1=p1->link)Attach(p1->coef,p1->expon,&rear);
	for(;p2;p2=p1->link)Attach(p2->coef,p2->expon,&rear);
	rear->link=NULL;
	temp=front;
	front = front->link;
	free(temp);
	return front;
}

Polynomial PolyMul(Polynomial p1,Polynomial p2)
{
	Polynomial p,Rear,t1,t2,t;
	int c,e;
	t1=p1;t2=p2;
	if(!p1||p2)return NULL;
	p = (Polynomial)malloc(sizeof(struct PolyNode));p->link = NULL;
	Rear = p;
	while(t2){	//先用p1的第一项乘p2等到链表p
		Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
		t2=t2->link;
	}
	t1->link;
	while (t1)
	{
		t2=p2;Rear = p;
		while (t2)
		{
			c=t1->coef*t2->coef;
			e=t1->expon+t2->expon;
			while(Rear->link && Rear->link->expon>e)
				Rear=Rear->link;
			if(Rear->link&&Rear->link->expon==e)
				if(Rear->link->coef+c)
					Rear->link->coef+=c;
				else{
					t = Rear->link;
					Rear->link=t->link;
					free(t);
				}
			else{
				t=(Polynomial)malloc(sizeof(struct PolyNode));
				t->coef=c;t->expon=e;
				t->link = Rear->link;
				Rear->link =t;Rear=t;
			}

		}
		t1=t1->link;
	}
	t2 = p;p=p->link;free(t2);

	return p;
}

void PrintPoly(Polynomial p)
{//输出多项式
	if(!p){
		printf("0 0\n");
		return;
	}

	while(p){
		printf("%d %d ",p->coef,p->expon);
		p = p ->link;
	}
	printf("\n");
}


void main()
{
	Polynomial p1,p2,pp,ps;
	p1=ReadPoly();
	p2=ReadPoly();
	pp = PolyMul(p1,p2);
	PrintPoly(pp);
	ps = PolyAdd(p1,p2);
	PrintPoly(ps);
}

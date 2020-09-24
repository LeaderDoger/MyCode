#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct PolyNode {
	double coef;	//系数
	int expon;	//指数
	struct PolyNode *link;	//指向下一个节点的指针
};
typedef struct PolyNode* Polynomial;
Polynomial P1,P2;

//由于在本函数中需要改变当前结果表达式尾项指针的值
//所以函数传递进来的是节点指针的地址，*pRear指向尾项
void Attach(double c,int e,Polynomial *pRear)
{	
	Polynomial p;

	p=(Polynomial)malloc(sizeof(struct PolyNode));
	p->coef =c;
	p->expon = e;
	p->link=NULL;
	//将p指向的新节点插入到当前结果表达式的尾项的后面
	(*pRear)->link = p;
	(*pRear)=p;//迭代
}

//将该项按指数升序插入到合适的位置
void InsertPoly(Polynomial head,Polynomial node)
{
	Polynomial q,p;
	q=head;
	p=head->link;
	while (p)
	{
		if(node->expon<=p->expon)break;
		p=p->link;
		q=q->link;
	}
	//遍历，找到插入位置
	node->link=q->link;
	q->link=node;
}

//多项式链表按指数排序
void OrderPoly(Polynomial head)
{
	Polynomial q,p;
	q=head->link;
	p=q;
	head->link=NULL;
	while ((p))
	{
		p=p->link;q->link=NULL;//截取节点
		InsertPoly(head,q);
		q=p;
	}
}

//建立多项式链表并排序
Polynomial ReadPoly()
{
	int N,e;
	double c;
	Polynomial Rear,P,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));//链表空节点
	P ->link = NULL;
	Rear = P;
	printf("请输入多项式的项数");
	scanf("%d",&N);
	if(N<=0)return NULL;
	while(N--){
		printf("请输入系数和指数:");
		scanf("%lf %d",&c,&e);
		Attach(c,e, &Rear);
	}
	OrderPoly(P);
	t = P;P = P->link;free(t);//删除临时头结点
	return P;
}

//比较指数大小
int Compare(int a,int b)
{
	if(a<b)return 1;
	if(b<a)return -1;
	return 0;
}

//多项式加法
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

//多项式减法
Polynomial PolySub (Polynomial p1,Polynomial p2)
{
	Polynomial front,rear,temp;
	int sub;
	rear=(Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;//由front记录结果多项式链表头结点
	while(p1&&p2)
		switch(Compare(p1->expon,p2->expon)){
		case 1:
			Attach(p1->coef,p1->expon,&rear);
			p1=p1->link;
			break;
		case -1:
			Attach(-p2->coef,p2->expon,&rear);
			p2=p2->link;
			break;
		case 0:
			sub =p1->coef-p2->coef;
			if(sub)Attach(sub,p1->expon,&rear);
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

//输出多项式
void PrintPoly(Polynomial p)
{
	if(!p){
		printf("0 0\n");
		return;
	}

	while(p){
		printf("%.2lf %d ",p->coef,p->expon);
		p = p ->link;
	}
	printf("\n");
}

void main()
{
	int sel;
	Polynomial p1,p2,ps;
	p1=ReadPoly();
	p2=ReadPoly();
	while(1){
		printf("请选择进行的运算:0-加法,1-减法\n");
		scanf("%d",&sel);
		if(sel==1){
			ps=PolySub(p1,p2);
			break;
		}
		if(sel==0) {
			ps=PolyAdd(p1,p2);
			break;
		}
	}
	PrintPoly(ps);
}
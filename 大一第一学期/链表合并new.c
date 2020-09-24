#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct student
{
	int score;
	struct student *next;//指针域
};
typedef struct student * Linklist;
//建立升序的链表
void Creatlist(Linklist head)
{
	int count = 1,i=0;//count：计数器,i：触发器
	int score,temp=-1;
	Linklist q;
	Linklist p;
	q = head;//对指针进行初始化
	printf("请输入第%d个同学的成绩:",count);
	scanf("%d",&score);
	temp=score;
	while(score!=-1){
		if(score!=-1&&score>=temp){
			p=(struct student*)malloc(sizeof(struct student));
			if(!p){printf("分配内存失败");exit(1);}
			p->score = score;
			q->next = p;
			q=p;	//迭代
			count++;
			temp=score;
		}
		else if(score<temp)printf("输入错误，请重新输入\n");
		printf("请输入第%d个同学的成绩:",count);
		scanf("%d",&score);
	}
	q->next =NULL;//收尾
}
//合并两个升序的链表
Linklist combine_list(struct student *head1,struct student *head2)
{
	Linklist p1,p2,head3,p=NULL,q=NULL;

	p1=head1->next;
	p2=head2->next;
	head3=(Linklist)malloc(sizeof(struct student));
	if(!head3){printf("分配内存失败");exit(1);}
	q=head3;

	//将小的先输入到合并的链表中
	while(p1&&p2){
		p=(Linklist)malloc(sizeof(struct student));
		if(!p){printf("分配内存失败");exit(1);}
		if(p1->score<p2->score){
			p->score=p1->score;
			q->next=p;
			q=q->next;
			p1=p1->next;
		}
		else
		{
			p->score=p2->score;
			q->next=p;
			q=q->next;
			p2=p2->next;
		}
	}
	//当其中一个链表到表尾时将另一个链表的数据接到表尾
	if(p1==NULL)p->next=p2;
	else p->next=p1;
	return head3;
}
//输出链表
void pri_list(struct student *head)
{
	int i=1;
	struct student *p=head->next;
	while(p){
		printf("第%d个人的成绩为%d\n",i++,p->score);
		p = p->next;
	}
}

void freelist(Linklist head)
{
	Linklist q=head,p=head->next;
	while(q->next){
		free(q);
		q=p;
		if(p->next)
			p->next;
	}
	free(q);
}

void main()
{
	Linklist list1,list2,list3,p;
	list1 = (struct student *)malloc(sizeof(struct student));
	if(!list1){printf("分配内存失败");exit(1);}
	list2 = (struct student *)malloc(sizeof(struct student));
	if(!list2){printf("分配内存失败");exit(1);}
	printf("建立第一个链表\n");
	Creatlist(list1);
	printf("建立第二个链表\n");
	Creatlist(list2);
	list3=combine_list(list1,list2);
	pri_list(list3);
	freelist(list1);
	freelist(list2);
	freelist(list3);
}
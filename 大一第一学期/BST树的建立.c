#include "base.h"

//链式存储树
typedef int ElementType;
typedef int Status;

typedef struct TNode* Position;
typedef Position BinTree; /* 二叉树类型 */

struct TNode { /* 树结点定义 */
	ElementType Data; /* 结点数据 */
	BinTree Left;     /* 指向左子树 */
	BinTree Right;    /* 指向右子树 */
};

//二叉搜索树中照最小值
BinTree Findmin(BinTree BST)
{
	if (!BST) return NULL;//空的二叉搜索树
	else if (!BST->Left)
		return BST;
	else
		return Findmin(BST->Left);
}

//二叉搜索树中照最大值
BinTree Findmax(BinTree BST)
{
	if (!BST) return NULL;//空的二叉搜索树
	else if (!BST->Right)
		return BST;
	else
		return Findmin(BST->Right);
}

//二叉搜索树的插入
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST) {//若原树为空，生成并返回一个节点的二叉搜索树
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else {//搜索插入元素的位置
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);//递归插入左子树
		else if (X > BST->Data)
			BST->Right = Insert(BST->Right, X);//递归插入右子树
		else;
	}
	return BST;
}

//二叉搜索树的删除 
BinTree Delete(BinTree BST, ElementType X, int* count)
{
	Position Tmp;
	if (!BST)printf("未找到要删除的元素");
	else {
		(*count)++;
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X, count);//从左子树递归删除
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X, count);//从右子树递归删除
		else {//BST就是要删除的节点
			if (BST->Left && BST->Right) {//如果被删除的节点有左右两个子节点
				//从右子树中找最小的元素填充删除结点
				Tmp = Findmin(BST->Right);
				BST->Data = Tmp->Data;
				BST->Right = Delete(BST->Right, BST->Data,count);
			}
			else {//被删除结点有一个或无子结点
				Tmp = BST;
				if (!BST->Left)
					BST = BST->Right;
				else
					BST = BST->Left;
				free(Tmp);
			}

		}

	}
	return BST;
}

//二叉树中序遍历
void InOrderTraversal(BinTree BT)
{
	if (BT) {
		InOrderTraversal(BT->Left);
		printf("%d,", BT->Data);
		InOrderTraversal(BT->Right);
	}

}

int Tree_seek(BinTree BT, ElementType X, Position* Node)
{
	if (!BT) {
		*Node = NULL;
		return 0;
	}
	if (BT->Data == X) {
		*Node = BT;
		return 1;
	}
	else {
		if (X < BT->Data)
			return Tree_seek(BT->Left, X, Node) + 1;
		else
			return Tree_seek(BT->Right, X, Node) + 1;
	}
}


int main()
{
	int nums[50] = { 241,267,934,300,969,724,478,758,762,664,
		305,345,281,227,561,691,795,942,227,836,
		591,404,902,353,492,582,821,516,718,895,
		847,326,571,538,469,912,267,899,435,494,
		903,811,322,933,273,864,941,711,453,668 };
	int num, i,count;
	BinTree BST = NULL;
	Position Node;

	printf("BST树中序遍历结果如下：\n");
	for (i = 0; i < 50; i++) {
		BST = Insert(BST, nums[i]);
	}
	InOrderTraversal(BST);

	printf("\n请输入查找的数字：\n");
	scanf("%d", &num);
	count = Tree_seek(BST, num, &Node);
	if (Node) {
		printf("查找成功，查找次数为：%d\n", count);
	}
	else printf("查找失败");

	printf("请输入删除的数字：\n");
	scanf("%d", &num);
	count = 0;
	BST = Delete(BST, num, &count);
	if(!BST)printf("查找成功，查找次数为：%d", count);
	printf("BST树删除后的中序遍历结果如下：\n");
	InOrderTraversal(BST);
}
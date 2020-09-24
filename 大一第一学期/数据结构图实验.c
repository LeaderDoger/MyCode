#include "base.h"


#define MaxVertexNum 100	/* 最大顶点数设为100 */
#define INFINITY 65535		/* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;			/* 用顶点下标表示顶点,为整型 */
typedef int WeightType;		/* 边的权值设为整型 */
typedef char DataType;      /* 顶点存储的数据类型设为字符型 */
typedef	 int ElementType;

Vertex Visited[MaxVertexNum] = { FALSE };//标记定点是否访问过的数组

typedef struct Node* PtrToNode;
struct Node { /* 队列中的结点 */
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode {
	Position Front, Rear;  /* 队列的头、尾指针 */
};
typedef struct QNode* Queue;

Queue CreatQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

Status IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}

ElementType DeleteQ(Queue Q)
{
	Position FrontCell;
	ElementType FrontElem;

	if (IsEmpty(Q)) {
		printf("队列空");
		return ERROR;
	}
	else {
		FrontCell = Q->Front;
		if (Q->Front == Q->Rear) /* 若队列只有一个元素 */
			Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
		else
			Q->Front = Q->Front->Next;
		FrontElem = FrontCell->Data;

		free(FrontCell);  /* 释放被删除结点空间  */
		return  FrontElem;
	}
}

Status AddQ(Queue Q, ElementType X)
{
	Position RearCell;
	RearCell = (Position)malloc(sizeof(struct QNode));
	RearCell->Data = X;
	if (!Q->Front && !Q->Rear)//没有元素
		Q->Front = Q->Rear = RearCell;
	else {
		Q->Rear->Next = RearCell;
		Q->Rear = Q->Rear->Next;
	}

	return 1;
}

/* 边的定义 */
typedef struct ENode* PtrToENode;
struct ENode {
	Vertex V1, V2;      /* 有向边<V1, V2> */
	WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接矩阵图结点的定义 */
typedef struct GNode1* PtrToGNode;
struct GNode1 {
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数  */
	WeightType G[MaxVertexNum][MaxVertexNum];/* 邻接矩阵 */
	DataType Data[MaxVertexNum];    /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

MGraph CreateGraph(int VertexNum)
{/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode1));/*建立图*/
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void Visit(Vertex V)
{
	printf("正在访问定点%d\n", V);
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* 若是无向图，还要插入边<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv, i;

	scanf("%d", &Nv);/* 读入顶点个数 */
	Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

	scanf("%d", &(Graph->Ne));   /* 读入边数 */
	if (Graph->Ne != 0) {/*如果有边*/
		E = (Edge)malloc(sizeof(struct ENode));/*建立边节点*/
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

Status IsEdge(MGraph Graph, Vertex V, Vertex W)
{
	return Graph->G[V][W] < INFINITY ? TRUE : FALSE;
}

void DFS(MGraph Graph, Vertex V)
{/* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	Vertex W;


	Visit(V);
	Visited[V] = TRUE;

	for (W = 0; W < Graph->Nv; W++) {
		if (!Visited[W] && IsEdge(Graph, V, W)) {
			DFS(Graph, W);
		}
	}
}

void DFS_1(MGraph Graph, Vertex V)
{
	DFS(Graph, V);
	memset(Visited, 0, MaxVertexNum);
}

void BFS(MGraph Graph, Vertex V)
{ /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
	Queue Q;
	Vertex  temp, W;

	Q = CreatQueue();/* 创建空队列, MaxSize为外部定义的常数 */
	/* 访问顶点S：此处可根据具体访问需要改写 */

	Visit(V);
	Visited[V] = TRUE; /* 标记S已访问 */
	AddQ(Q, V);/* V入队列 */

	while (!IsEmpty(Q)) {
		temp = DeleteQ(Q);/* 弹出temp */

		for (W = 0; W < Graph->Nv; W++) {/* 对图中的每个顶点W */
			/* 若W是V的邻接点并且未访问过 */
			if (!Visited[W] && IsEdge(Graph, temp, W)) {
				Visit(W);
				Visited[W] = TRUE;/* 标记W已访问 */
				AddQ(Q, W);/* W入队列 */
			}
		}
	}
	memset(Visited, 0, MaxVertexNum);
}

Vertex FindMinDist(MGraph Graph, WeightType dist[])
{ /* 返回未被收录顶点中dist最小者 */
	Vertex MinV, V;
	WeightType MinDist = INFINITY;

	for (V = 0; V < Graph->Nv; V++) {
		if (dist[V] != 0 && dist[V] < MinDist) {
			/* 若V未被收录，且dist[V]更小 */
			MinDist = dist[V]; /* 更新最小距离 */
			MinV = V; /* 更新对应顶点 */
		}
	}
	if (MinDist < INFINITY) /* 若找到最小dist */
		return MinV; /* 返回对应的顶点下标 */
	else return ERROR;  /* 若这样的顶点不存在，返回-1作为标记 */
}






/* 邻接点的定义 */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;        /* 邻接点下标 */
	WeightType Weight;  /* 边权重 */
	PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;/* 边表头指针 */
	DataType Data;            /* 存顶点的数据 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode2* PtrToGNode2;
struct GNode2 {
	int Nv;     /* 顶点数 */
	int Ne;     /* 边数   */
	AdjList G;  /* 邻接表 */
};
typedef PtrToGNode2 LGraph; /* 以邻接表方式存储的图类型 */

LGraph CreateGraph2(int VertexNum)
{/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode1));/* 建立图 */
	Graph->Nv = VertexNum;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge2(LGraph Graph, Edge E)
{/*将边插入图中*/
	PtrToAdjVNode NewNode;
	/* 插入边 <V1, V2> */
	/* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头(头插法) */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph2()
{
	LGraph Graph;
	Edge E;
	int Nv, i;

	scanf("%d", &(Nv));   /* 读入顶点个数 */
	Graph = CreateGraph2(Nv); /* 初始化有Nv个顶点但没有边的图 */

	scanf("%d", &(Graph->Ne));   /* 读入边数 */
	if (Graph->Ne != 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdge2(Graph, E);
		}
	}

	return Graph;
}

/* 邻接表存储的图 - DFS */
void Visit2(Vertex V)
{
	printf("正在访问定点%d\n", V);
}

/* Visited[]为全局变量，已经初始化为FALSE */
void DFS2(LGraph Graph, Vertex V)
{/* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;


	Visit2(V);/* 访问第V个顶点 */
	Visited[V] = TRUE; /* 标记V已访问 */

	for (W = Graph->G[V].FirstEdge; W; W = W->Next)/* 对V的每个邻接点W->AdjV */
		if (!Visited[W->AdjV]) {/* 若W->AdjV未被访问 */
			DFS2(Graph, W->AdjV);/* 则递归访问之 */
		}
}

void DFS_2(LGraph Graph, Vertex V)
{
	DFS2(Graph, V);
	memset(Visited, 0, MaxVertexNum);
}

void BFS2(LGraph Graph, Vertex V)
{
	PtrToAdjVNode W;
	Vertex temp;
	Vertex visited[MaxVertexNum] = { FALSE };
	Queue Q;

	Q = CreatQueue();

	Visit2(V);
	visited[V] = TRUE;
	AddQ(Q, V);//将该节点入队
	while (!IsEmpty(Q)) {//若队列不为空
		temp = DeleteQ(Q);//出队
		for (W = Graph->G[temp].FirstEdge; W; W = W->Next)/* 对出队的顶点的每个邻接点W->AdjV */
			if (!visited[W->AdjV]) {
				Visit2(W->AdjV);
				visited[W->AdjV] = TRUE;
				AddQ(Q, W->AdjV);
			}
	}
	memset(Visited, 0, MaxVertexNum);
}



int Prim(MGraph Graph, LGraph* MST)
{ /* 将最小生成树保存为邻接表存储的图MST，返回最小权重和 */
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge E;

	/* 初始化。默认初始点下标是0 */
	for (V = 0; V < Graph->Nv; V++) {
		/* 这里假设若V到W没有直接的边，则Graph->G[V][W]定义为INFINITY */
		dist[V] = Graph->G[0][V];
		parent[V] = 0; /* 暂且定义所有顶点的父结点都是初始点0 */
	}
	/* 创建包含所有顶点但没有边的图。注意用邻接表版本 */
	*MST = CreateGraph2(Graph->Nv);
	TotalWeight = 0; /* 初始化权重和     */
	VCount = 0;;/* 初始化收录的顶点数 */
	(*MST)->Ne = 0;/* 初始化收录的边数 */
	E = (Edge)malloc(sizeof(struct ENode)); /* 建立空的边结点 */

	/* 将初始点0收录进MST */
	dist[0] = 0;
	VCount++;
	parent[0] = -1; /* 当前树根是0 */

	while (1) {
		V = FindMinDist(Graph, dist);
		/* V = 未被收录顶点中dist最小者 */
		if (V == ERROR) /* 若这样的V不存在 */
			break;   /* 算法结束 */

		/* 将V及相应的边<parent[V], V>收录进MST */
		E->V1 = parent[V];
		E->V2 = V;
		E->Weight = dist[V];
		InsertEdge2(*MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		(*MST)->Ne++;
		VCount++;

		for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
			if (dist[W] != 0 && Graph->G[V][W] < INFINITY) {
				/* 若W是V的邻接点并且未被收录 */
				if (Graph->G[V][W] < dist[W]) {
					/* 若收录V使得dist[W]变小 */
					dist[W] = Graph->G[V][W]; /* 更新dist[W] */
					parent[W] = V; /* 更新树 */
				}
			}
	} /* while结束*/
	if (VCount < Graph->Nv) /* MST中收的顶点不到|V|个 */
		TotalWeight = ERROR;
	return TotalWeight;   /* 算法执行完毕，返回最小权重和或错误标记 */
}




int main()
{
	MGraph Mgraph;
	LGraph Lgraph, Mintree;
	Vertex V1, V2;
	printf("请输入图1：\n");
	Mgraph = BuildGraph();
	printf("请输入图2：\n");
	Lgraph = BuildGraph2();

	//邻接矩阵
	printf("邻接矩阵实现：\n");
	printf("请输入遍历图1的起点：");
	scanf("%d", &V1);
	printf("DFS遍历结果如下：\n");
	DFS_1(Mgraph, V1);
	printf("\n");
	printf("BFS遍历结果如下：\n");
	BFS(Mgraph, V1);
	printf("\n");
	printf("该图的最小生成树BFS遍历结果如下：\n");
	Prim(Mgraph, &Mintree);
	DFS_2(Mintree, 0);
	printf("\n");

	//邻接表
	printf("邻接表实现：\n");
	printf("请输入遍历图2的起点：");
	scanf("%d", &V2);
	printf("DFS遍历结果如下：\n");
	DFS_2(Lgraph, V2);
	printf("\n");
	printf("BFS遍历结果如下：\n");
	BFS2(Lgraph, V2);

}
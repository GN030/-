/*----邻接表中，深度优先搜索DFS实现思路
1,首先定义全局变量bool Visited[],储存每个顶点V的访问标记，并初始化为false
2,首先将顶点V标记为已访问；若邻接点指针W(W=Graph->G[V].FirstEdge)不为空，判断邻接点是否被访问过；
3,若未被访问过，则递归调用DFS（Graph,W-AdjV,Visit）;
4,递归结束，继续判断顶点V的下一个邻接点W=W->Next;*/

/*----邻接表中，广度优先搜索BFS实现思路(自己补充)
1,首先定义全局变量bool Visited[],储存每个顶点V的访问标记，并初始化为false
2,创建空队，访问顶点下标S，并将顶点下标S入队；
3,如果队非空，出队一个顶点下标X；若顶点下标X存在邻接点指针Y（Y=Graph->G[X].FirstEdge!=NULL）且未被访问过，访问并标记Y，将顶点Y->AdjV入队；
4,如此检查顶点X的所有邻接点（Y=Y->Next）;
5,步骤3，4循环执行，直至队列空。*/

/*图的邻接表思路
1,定义一个边的结构体ENode,存储有向边<Vq1,V2>,和该边的权重Weight；
2,图结点通过定义结构体GNode，存储顶点数Nv，边数Ne和邻接表G；
2,邻接表G是一个指针数组，其中每一个指针都指向一个顶点表头结点Vnode；
2,顶点表头结点Vnode存储了一个边表头指针FirstEdge，和该位置顶点的数据
2,FirstEdge是一个邻接点类型的结构体指针，邻接点结构体包含了邻接点的下标AdjV，顶点与邻接点的边权重，和下一个邻接点指针变量。
3,初始化一个空图：对图结点申请空间，初始化顶点数Nv，边数Ne和邻接表G中指针为NULL；
4,插入边：根据输入数据建立一个边结点结构体ENode，创建邻接点结构体AdjVNode并申请空间，对其下标、权重进行赋值，将Graph->G[E->V2].FirstEdge链接在AdjVNode->Next中，并将AdjVNode指针存放在Graph->G[E->V2].FirstEdge中；
5,建立图：读入顶点个数，并初始化空图；逐个读入每一条边，存入边结构体ENode，并插入图Graph中；若有顶点数据，将其存入Graph->G[i].Data中。
*/

/*注意&必读：
1,这里默认顶点编号从0开始，到(Graph->Nv - 1) ,所以你在用的时候要额外注意输入的顶点从0还是从1开始
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElementType int
#define MaxSize 100
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MaxSize];
    int rear;  //记录尾元素序号
    int front; //记录头元素序号
};

/* 图的邻接表表示法 */
#define MaxVertexNum 100 /* 最大顶点数设为100 */
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;   /* 顶点存储的数据类型设为字符型 */

bool Visited[MaxVertexNum] = {false}; //结点是否被访问过的标志

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;     /* 有向边<V1, V2> */
    WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
    DataType Data;           /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum]; /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    /* 顶点数 */
    int Ne;    /* 边数   */
    AdjList G; /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */


void AddQ(Queue PtrQ, ElementType item); //入队列，队列采用循环结构可以最大限度利用空间
ElementType DeleteQ(Queue PtrQ);         //出队列
int IsEmpty(Queue PtrQ);                 /*队列空，返回1*/
Queue CreateQueue();                     /*创建空队*/



/* 邻接表存储的图 - DFS&BFS(自己实现，可能有错误) */
void Visit(Vertex V)
{
    printf("正在访问顶点%d\n", V);
}

/* Visited[]为全局变量，已经初始化为false */
void DFS(LGraph Graph, Vertex V, void (*Visit)(Vertex))
{                    /* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
    PtrToAdjVNode W; //邻接点指针

    Visit(V);          /* 访问第V个顶点 */
    Visited[V] = true; /* 标记V已访问 */

    for (W = Graph->G[V].FirstEdge; W; W = W->Next) /* 对V的每个邻接点W->AdjV */
        if (!Visited[W->AdjV])                      /* 若W->AdjV未被访问 */
            DFS(Graph, W->AdjV, Visit);             /* 则递归访问之 */
}

/* Visited[]为全局变量，已经初始化为false */
void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex))
{ /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;
    Vertex V;//顶点下标V
    PtrToAdjVNode W;//邻接点指针W

    Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
    /* 访问顶点S：此处可根据具体访问需要改写 */
    Visit(S);
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Q, S);        /* S入队列 */

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);                 /* 弹出V */
        for (W=Graph->G[V].FirstEdge; W; W=W->Next) /* 对顶点V的每一个邻接点*/
            /* 若邻接点W并且未访问过 */
            if (!Visited[W->AdjV])
            {
                /* 访问顶点W */
                Visit(W->AdjV);
                Visited[W->AdjV] = true; /* 标记W已访问 */
                AddQ(Q, W->AdjV);        /* W入队列 */
            }
    } /* while结束*/
}

// 04.创建空队
Queue CreateQueue()
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->front = 0;
    Q->rear = MaxSize;
    return Q;
}
// 02.入队列，队列采用循环结构可以最大限度利用空间
void AddQ(Queue PtrQ, ElementType item)
{
    if ((PtrQ->rear + 1) % MaxSize == PtrQ->front)
    {
        printf("队列满");
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
    PtrQ->Data[PtrQ->rear] = item;
}
// 03.出队列
ElementType DeleteQ(Queue PtrQ)
{
    ElementType item;
    if (PtrQ->front == PtrQ->rear)
    {
        printf("队列空");
        return 0;
    }
    PtrQ->front = (PtrQ->front + 1) % MaxSize;
    return (PtrQ->Data[PtrQ->front]);
}
//判断是否空
int IsEmpty(Queue PtrQ)
{
    if (PtrQ->front == PtrQ->rear)
    {
        // printf("队列空");
        return 1;
    }
    else
        return 0;
}

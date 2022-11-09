/*----邻接矩阵中，广度优先搜索BFS设计思路：
1,首先定义全局变量bool Visited[],储存每个顶点V的访问标记，并初始化为false
2,创建空队，将顶点下标入队；
3,如果队非空，出队一个元素X，逐个检查所有顶点是否为邻接点；若顶点Y为邻接点(Graph->G[X][Y]=1)，且未被访问过，访问Y并标记Y，将顶点Y入队
4,步骤3循环执行，直至队列空。*/

/*----邻接矩阵中,深度优先搜索DFS设计思路：（自己补充）
1,首先定义全局变量bool Visited[],储存每个顶点V的访问标记，并初始化为false;
2,首先将顶点V标记为已访问，接下来逐个检查所有顶点是否为S的邻接点；
3,若顶点W为邻接点（Graph->G[X][Y]=1），且未被访问过，递归调用DFS（Graph,Y,visit）
3,递归结束，继续判断顶点S的下一个邻接点W++；
*/

/*邻接矩阵表示思路：
1,定义边对应的结构体ENode,其中存储有向边<Vq1,V2>,和该边的权重；
2,定义图结点对应的结构体GNode，其中存储顶点数Nv,边数Ne，邻接矩阵G[预设值][预设值]（用邻接矩阵的顶点下标表示顶点）（矩阵元素对应每个单向边的权重）,以及每个顶点的数据（比如边的名字）
3,初始化图：一个具有N个顶点，但无边的图，要申请图结点空间GNode，初始化其中各项值
4,插入边：将边结构体ENode其中的单向边值和权重值传入图结点GNode；
5,建立图：读入顶点数，初始化一个空图，读入所有边数据存入邻接矩阵中，读入每个结点的数据存入Data；
*/

/*注意&必读：
1,这里默认顶点编号从0开始，到(Graph->Nv - 1) ,所以你在用的时候要额外注意输入的顶点从0还是从1开始
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*队列的矩阵存储实现*/
#define ElementType int
#define MaxSize 10000
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MaxSize];
    int rear;  //记录尾元素序号
    int front; //记录头元素序号
};

/*图的邻接矩阵表示方法*/
#define MaxVertexNum 100 /*最大顶点数*/
#define INFINITY 65535   /*无穷设为双字节无符号整数的最大值65535*/

bool Visited[MaxVertexNum] = {false}; //结点是否被访问过的标志

typedef int Vertex;     /*用顶点下标表示顶点，为整型*/
typedef int WeightType; /*边的权值设为整型*/
typedef char DataType;  /*顶点存储的数据类型设为字符型*/
/*边的定义*/
typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;     /*有向边<V1,V2>*/
    WeightType Weight; /*权重*/
};
typedef PtrToENode Edge;
/*图结点的定义*/
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                   /*顶点数*/
    int Ne;                                   /*边数*/
    WeightType G[MaxVertexNum][MaxVertexNum]; /*邻接矩阵*/
    DataType Data[MaxVertexNum];              /*存顶点的数据*/
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

/*BFS和DFS相关函数声明*/
bool IsEdge(MGraph Graph, Vertex V, Vertex W);
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex));/* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
void DFS(MGraph Graph, Vertex S, void (*Visit)(Vertex)); /* 以S为出发点对邻接矩阵存储的图Graph进行DFS搜索 */
void Visit(Vertex);

/*队列相关函数声明(线性存储)*/
Queue CreateQueue();// 04.创建空队
void AddQ(Queue PtrQ, ElementType item);// 02.入队列，队列采用循环结构可以最大限度利用空间
ElementType DeleteQ(Queue PtrQ);// 03.出队列
int IsEmpty(Queue PtrQ);//判断是否为空


/* 深度优先搜索实现BFS-基于邻接矩阵 */
/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
bool IsEdge(MGraph Graph, Vertex V, Vertex W)
{
    return Graph->G[V][W] < INFINITY ? true : false;
}

void Visit(Vertex V)
{
    printf(" %d", V);
}

/* Visited[]为全局变量，已经初始化为false */
void BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{ /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    Queue Q;
    Vertex V, W;

    Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
    /* 访问顶点S：此处可根据具体访问需要改写 */
    Visit(S);
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Q, S);        /* S入队列 */

    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q);                 /* 弹出V */
        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if (!Visited[W] && IsEdge(Graph, V, W))
            {
                /* 访问顶点W */
                Visit(W);
                Visited[W] = true; /* 标记W已访问 */
                AddQ(Q, W);        /* W入队列 */
            }
    } /* while结束*/
}
/* Visited[]为全局变量，已经初始化为false */
void DFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    Vertex W;
    /*访问顶点S：此处可以根据具体访问需要改写*/
    Visit(S);
    Visited[S] = true;              /*标记S已访问*/
    for (W = 0; W < Graph->Nv; W++) /*对图中的每个顶点W*/
    {                               /*若W是S的邻接点且未被访问过*/
        if (!Visited[W] && IsEdge(Graph, S, W))
        {
            DFS(Graph, W, Visit);
        }
    }
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
/*题意分析：六度空间理论，判定一张图中符合六度空间的结点站所有节点的百分比;首先输入顶点数N和边数M;
最后打印对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。*/
/*思路：
1,使用邻接矩阵存储,广度优先搜索方法;
2,实现广度优先搜索关于层数的判别:last2保存每层最后一个结点，last1保存每次向下搜索层的最后一个结点；当last2==当前顶点V时，将last2=last1，层数level++；
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>/* 此为memset()需调用的库函数*/
#include <stdbool.h>

/*队列的矩阵存储实现*/
#define ElementType int
#define MaxSize 1001
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MaxSize];
    int rear;  //记录尾元素序号
    int front; //记录头元素序号
};

/*图的邻接矩阵表示方法*/
#define MaxVertexNum 1001 /*最大顶点数*/
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

/*创建图的相关函数声明(邻接矩阵表示)*/
MGraph CreateGraph(int VertexNum);     /* 初始化一个有VertexNum个顶点但没有边的图 */
void InsertEdge(MGraph Graph, Edge E); /*插入边*/
MGraph BuildGraph();                   /*建立图*/

/*队列相关函数声明(线性存储)*/
Queue CreateQueue();                     // 04.创建空队
void AddQ(Queue PtrQ, ElementType item); // 02.入队列，队列采用循环结构可以最大限度利用空间
ElementType DeleteQ(Queue PtrQ);         // 03.出队列
int IsEmpty(Queue PtrQ);                 //判断是否为空

/*BFS和DFS相关函数声明*/
bool IsEdge(MGraph Graph, Vertex V, Vertex W);
int BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex));  /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
void DFS(MGraph Graph, Vertex S, void (*Visit)(Vertex)); /* 以S为出发点对邻接矩阵存储的图Graph进行DFS搜索 */
void Visit(Vertex);

int main(void)
{
    int value;
    float percent;
    MGraph G;
    G = BuildGraph();
    value = 0; /*与目标结点不超过六层的结点数*/
    for (Vertex i = 0; i < G->Nv; i++) 
    {
        value = BFS(G, i, Visit);
        memset(Visited, false, G->Nv); /*每次都要初始化Visited[]*/
        percent = (((float)value+1) / (float)G->Nv);
        printf("%d: %.2f%%\n", i+1, percent*100);
    }
    return 0;
}

MGraph CreateGraph(int VertexNum)
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V = 0; V < Graph->Nv; V++)
        for (W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{/*输入边的起始1开始，这里要做修改*/
    /* 插入边 <V1, V2> */
    Graph->G[(E->V1)-1][(E->V2)-1] = E->Weight;
    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[(E->V2)-1][(E->V1)-1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);        /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */

    scanf("%d", &(Graph->Ne)); /* 读入边数 */
    if (Graph->Ne != 0)
    {                                           /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i = 0; i < Graph->Ne; i++)
        {
            scanf("%d %d", &E->V1, &E->V2);
            E->Weight = 1;
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
    }

    // /* 如果顶点有数据的话，读入数据 */
    // for (V = 0; V < Graph->Nv; V++)
    //     scanf(" %c", &(Graph->Data[V]));

    return Graph;
}

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
int BFS(MGraph Graph, Vertex S, void (*Visit)(Vertex))
{ /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    int level, count;
    level = -1;
    count = 0;
    Queue Q;
    Vertex V, W, last1, last2;
    Q = CreateQueue(MaxSize); /* 创建空队列, MaxSize为外部定义的常数 */
    /* 访问顶点S：此处可根据具体访问需要改写 */
    // Visit(S);
    Visited[S] = true; /* 标记S已访问 */
    AddQ(Q, S);        /* S入队列 */
    level = 0;
    last2=S;
    while (!IsEmpty(Q))
    {
        V = DeleteQ(Q); /* 弹出V */
        for (W = 0; W < Graph->Nv; W++) /* 对图中的每个顶点W */
            /* 若W是V的邻接点并且未访问过 */
            if (!Visited[W] && IsEdge(Graph, V, W))
            {
                /* 访问顶点W */
                // Visit(W);
                Visited[W] = true; /* 标记W已访问 */
                AddQ(Q, W);        /* W入队列 */
                count++;
                last1 = W; /*当前顶点V的最后一个邻接点下标*/
            }
        if(V==last2)/*当前层的最后一个顶点下标V的邻接点已经全部找到*/
        {
            last2=last1;//保存下一层的最后一个顶点下标
            level++;/*第ans层遍历结束*/
        }
        if (level==6)
        break;
        
    }              /* while结束*/
    return count;
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
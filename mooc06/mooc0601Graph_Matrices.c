
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

/*创建图的相关函数声明(邻接矩阵表示)*/
MGraph CreateGraph(int VertexNum);     /* 初始化一个有VertexNum个顶点但没有边的图 */
void InsertEdge(MGraph Graph, Edge E); /*插入边*/
MGraph BuildGraph();                   /*建立图*/

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
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge(Graph, E);
        }
    }

    /* 如果顶点有数据的话，读入数据 */
    for (V = 0; V < Graph->Nv; V++)
        scanf(" %c", &(Graph->Data[V]));

    return Graph;
}
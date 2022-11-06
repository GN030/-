/*题目分析：湖的大小100*100，007在岛的中心，岛半径15，每次能跳D距离远，第一行输入鳄鱼个数N和距离D，若能上岸打印'Yes'，否则'No'*/
/*思路分析：
1,Crocs矩阵存储鳄鱼坐标（0-100），Coast矩阵存储能否上岸，默认值为0；
2,
3,
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define Maxsize 100
#define ElementType int
typedef struct Graph *PtrGraph;
bool Visited[Maxsize][Maxsize] = {false}; //结点是否被访问过的标志
struct Graph
{
    ElementType Crocs[Maxsize][Maxsize]; //存鳄鱼的位置坐标，1表示有鳄鱼
    bool Up[Maxsize][Maxsize];           //存该点能否上岸，1表示能上岸
    int V;                               //顶点数
};

void Insert(int x1, int y1, int D, PtrGraph PtrG); //将鳄鱼坐标插入坐标图，并计算该点能否上岸。
int DFS(PtrGraph PtrG, int x1, int y1, int D);     //深度优先搜索
int IsNear(int x1, int y1, int x2, int y2, int D); //判断能否调到，能挑到返回1
void pause(void);                                  //暂停函数，方便调试
int main(void)
{
    struct Graph G = {0, false}; //初始化结构体G
    PtrGraph PtrG = &G;
    int N, D, i, j, x1, y1, count, mark;
    mark = 0;
    scanf("%d%d", &N, &D);
    for (i = 0; i < N; i++)
    {
        scanf("%d%d", &x1, &y1); //横纵坐标范围（-50，50）
        Insert(x1, y1, D, PtrG); //将鳄鱼坐标插入坐标图，并计算该点能否上岸。
    }
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        { //查找007在岛上能跳到的,未被访问过的鳄鱼（距离岛15+D范围内的鳄鱼）
            if (G.Crocs[i][j] == 1 && IsNear(50, 50, i, j, 15 + D) && Visited[i][j] == false)
                mark = DFS(PtrG, i, j, D);
            if (mark)
                break;
        }
        if (mark)
            break;
        // if (i == 14)
        //     pause();
    }
    if (mark)
        printf("Yes");
    else
        printf("No");
    return 0;
}
void pause(void)
{
    return;
}
void Insert(int x1, int y1, int D, PtrGraph PtrG)
{
    PtrG->Crocs[x1 + 50][y1 + 50] = 1;
    if ((abs(x1) + D) >= 50 || (abs(y1) + D) >= 50)
    {
        PtrG->Up[x1 + 50][y1 + 50] = true;
    }
}
int DFS(PtrGraph PtrG, int x1, int y1, int D)
{ //深度优先搜索
    int i, j, mark;
    mark = 0;
    Visited[x1][y1] = true;
    if (PtrG->Up[x1][y1] == true)
        return 1;
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 100; j++)
        { //查找跳到的鳄鱼附近D距离内的未被访问过的鳄鱼，并遍历它
            if (PtrG->Crocs[i][j] == 1 && IsNear(x1, y1, i, j, D) && Visited[i][j] == false)
                mark = DFS(PtrG, i, j, D); //深度遍历点（i,j）
            if (mark)
                break;
        }
        if (mark)
            break;
    }
    if (mark)
        return 1;
    else
        return 0;
}
int IsNear(int x1, int y1, int x2, int y2, int D)
{ //判断能否跳到，能挑到返回1
    int dx = x1 - x2;
    int dy = y1 - y2;
    if ((dx * dx + dy * dy) <= D * D)
        return 1;
    else
        return 0;
}
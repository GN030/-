//题目要求：从上到下，从左到右的顺序输出叶结点
//解题思路：应采用层序遍历的方法，进行输出；采用链表数组形式来存储二叉树；记录每个二叉树的根节点；采用队列方法进行层序遍历
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10
#define Null -1
struct TreeNode
{
    int Left;
    int Right;
} T1[MaxSize];
static struct QueueNode
{
    int Data[MaxSize];
    int front;
    int rear;
} Q;
int BuildTree(struct TreeNode T[MaxSize]); //接收输入建立二叉树，并返回二叉树根节点的序号Root
void LevelOderPrintLeaves(int Root);       //按照层序遍历的顺序，输出二叉树叶结点序号
void Add(struct QueueNode *Qp, int Data);  //入队列
int DeleteQueue(struct QueueNode *Qp);     //出队列
int main(void)
{
    int Root1; //二叉树的叶结点
    Root1 = BuildTree(T1);
    LevelOderPrintLeaves(Root1);
    return 0;
}
int BuildTree(struct TreeNode T[MaxSize])
{
    int N, Root, i;
    scanf("%d", &N);
    // printf("N=%d\n", N);
    if (N) //输入二叉树非空
    {
        int check[MaxSize]; //用于记录根节点位置，根节点对应位置为0，其余位置为1
        char tl, tr;
        for (i = 0; i < N; i++)
        {
            check[i] = 0;
        }
        for (i = 0; i < N; i++)
        {
            scanf(" %c %c", &tl, &tr);
            if (tl != '-') //若左子树存在，记录左子树序号
            {
                T[i].Left = tl - '0';
                check[T[i].Left] = 1;
            }
            else //若左子树不存在，将左子树序号记为Null=-1；
                T[i].Left = Null;
            if (tr != '-')
            {
                T[i].Right = tr - '0';
                check[T[i].Right] = 1;
            }
            else
                T[i].Right = Null;
        }
        for (i = 0; i < N; i++) //找到根节点位置
        {
            if (!check[i])
            {
                Root = i;
                break;
            }
        }
    }
    else
        Root = Null;
    // printf("Root:%d\n", Root);
    return Root;
}
void LevelOderPrintLeaves(int Root)
{                     //按照层序遍历的顺序输出叶结点
int i=0;//输出空格的标志
    if (Root == Null) //二叉树为空，直接返回
        return;
    Q.front = 0; //初始化队列Q
    Q.rear = 0;
    Add(&Q, Root);            //将根结点序号送入队列
    while (Q.rear != Q.front) //队列非空，表示二叉树还没结束
    {
        Root = DeleteQueue(&Q);                                  //输出当前结点的序号
        if ((T1[Root].Left == Null) && (T1[Root].Right == Null)) //左子树，右子树均不存在，为叶子结点，并输出结点序号Root
        {
            if (i)
                printf(" ");
            printf("%d", Root);
            i=1;
        }
        if (T1[Root].Left != Null) //左子树非空，将左子树序号存入队列中
            Add(&Q, T1[Root].Left);
        if (T1[Root].Right != Null) //右子树非空，将右子树序号存入队列中
            Add(&Q, T1[Root].Right);
    }
}
void Add(struct QueueNode *Qp, int Data)
{
    if ((Qp->rear + 1) % MaxSize == Qp->front)
    {
        printf("队列满");
        return;
    }
    Qp->Data[Qp->rear] = Data;
    Qp->rear = (Qp->rear + 1) % MaxSize;
    return;
}
int DeleteQueue(struct QueueNode *Qp)
{
    int item;
    if (Qp->rear == Qp->front)
    {
        printf("队列空");
        return -1;
    }
    item = Qp->Data[Qp->front];
    Qp->front = (Qp->front + 1) % MaxSize;
    return item;
}
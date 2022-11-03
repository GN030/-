//作业4-1同mooc0403JudgeSameBST
//注意，标志位在置位时，尽量将其设置为置1语句，不容易出错。
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct BSTNode *Position;
typedef Position BSTree; /* 二叉搜索树类型 */
struct BSTNode
{
    ElementType Data; /* 结点数据 */
    BSTree Left;      /* 指向左子树 */
    BSTree Right;     /* 指向右子树 */
    int flag;         //结点被访问过的标志
};

BSTree MakeTree(int N);                 //根据输入建立一个二叉搜索树T，并返回首结点地址
BSTree Insert(BSTree T, ElementType v); //向二叉搜索树中插入一个结点v；
int Judge(BSTree T, int N);             //判断输入序列与二叉搜索树T是否匹配，匹配返回1
int check(BSTree T, ElementType X);     //在树T中搜索结点元素X，若所经过结点的flag标志为1，则继续向子树元素检查；若flag为0，且结点与x相等，则返回1
void ResetT(BSTree T);                  //重置树T中的标志数据flag
void FreeTree(BSTree T);                //释放掉树T的空间

int main(void)
{
    int N, L; // N是二叉树结点数，L是后面需要判断的序列个数
    BSTree T;
    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        T = MakeTree(N);
        for (int i = 0; i < L; i++)
        {
            if (Judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            ResetT(T); //清楚T中标记falg
        }
        FreeTree(T);
        scanf("%d", &N); //输入下一个判别序列的结点数N
    }
    return 0;
}
BSTree MakeTree(int N)
{ //建立第一颗树
    BSTree T = (BSTree)malloc(sizeof(struct BSTNode));
    T->flag = 0;
    T->Left = NULL;
    T->Right = NULL;
    int v, i;
    scanf("%d", &v);
    T->Data = v;
    for (i = 1; i < N; i++)
    {
        scanf("%d", &v);
        T = Insert(T, v);
    }
    return T;
}
BSTree Insert(BSTree T, ElementType v)
{ //向二叉搜索树中插入一个结点v；
    if (!T)
    {
        T = (BSTree)malloc(sizeof(struct BSTNode));
        T->Data = v;
        T->flag = 0;
        T->Left = NULL;
        T->Right = NULL;
    }
    else
    {
        if (v > T->Data)
            T->Right = Insert(T->Right, v);
        else
            T->Left = Insert(T->Left, v);
    }
    return T;
}
int Judge(BSTree T, int N) //判断是否匹配，匹配返回1
{
    int v, flag = 0; // flag为不匹配标志位
    scanf("%d", &v);
    if (v != T->Data)
        flag = 1;
    else
        T->flag = 1;
    for (int i = 1; i < N; i++)
    {
        scanf("%d", &v);
        if ((!flag) && (!check(T, v))) //存在不匹配的情况
            flag = 1;
    }
    if (flag)
        return 0;
    else
        return 1;
}
int check(BSTree T, ElementType X)
//在树T中搜索结点元素X，若所经过结点的flag标志为1，则继续向子树元素检查；若flag为0，且结点与x相等，则返回1
{
    if (T->flag) //结点元素被访问过
    {
        if (X > T->Data)
            return check(T->Right, X);
        else if (X < T->Data)
            return check(T->Left, X);
        else
            return 0;
    }
    else //结点元素没有被访问过
    {
        if (X == T->Data)
        {
            T->flag = 1;
            return 1;
        }
        else
            return 0;
    }
}
void ResetT(BSTree T)
{
    if (T->Left)
        ResetT(T->Left);
    if (T->Right)
        ResetT(T->Right);
    T->flag = 0;
}
void FreeTree(BSTree T)
{
    if (T->Left)
        FreeTree(T->Left);
    if (T->Right)
        FreeTree(T->Right);
    free(T);
}
//测试输入：
// 4 2
// 3 1 4 2
// 3 4 1 2
// 3 2 4 1
// 2 1
// 2 1
// 1 2
// 0
//测试输出
// Yes
// No
// No
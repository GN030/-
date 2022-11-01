//输入一个序列，按照平衡二叉树原则进行插入，并找到它的根节点
//思路：每次插入一个结点，更新每个结点的平衡因子，找到“发现者”，并判断需要进行哪种处理。
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode
{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};
int Max(int a, int b);
AVLTree SingleLeftRotation(AVLTree A);
AVLTree SingleRightRotation(AVLTree A);
AVLTree DoubleLeftRightRotation(AVLTree A);
AVLTree DoubleRightLeftRotation(AVLTree A);
AVLTree Insert(AVLTree T, ElementType X);
int GetHeight(AVLTree BT);
int main(void)
{
    int N, v; // N为输入结点个数，v表示每次输入数据。
    scanf("%d", &N);
    AVLTree T=NULL;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v);
        T=Insert(T, v);
    }
    printf("%d\n", T->Data);
    return 0;
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

AVLTree SingleLeftRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}
//右单旋，自己补充
AVLTree SingleRightRotation(AVLTree A)
{ /* 注意：A必须有一个右子结点B */
    /* 将A与B做右单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{ /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}
//右-左双旋，自己补充
AVLTree DoubleRightLeftRotation(AVLTree A)
{ /* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做左单旋，C被返回 */
    A->Right = SingleLeftRotation(A->Right);
    /* 将A与C做左单旋，C被返回 */
    return SingleRightRotation(A);
}

/*************************************/
/* 对称的右单旋与右-左双旋请自己实现 */
/*************************************/

AVLTree Insert(AVLTree T, ElementType X)
{ /* 将X插入AVL树T中，并且返回调整后的AVL树 */
    if (!T)
    { /* 若插入空树，则新建包含一个结点的树 */
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Right = NULL;
        T->Left = NULL;
    } /* if (插入空树) 结束 */

    else if (X < T->Data)
    {
        /* 插入T的左子树 */
        T->Left = Insert(T->Left, X);
        /* 如果需要左旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
            if (X < T->Left->Data)
                T = SingleLeftRotation(T); /* 左单旋 */
            else
                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
    }                                           /* else if (插入左子树) 结束 */

    else if (X > T->Data)
    {
        /* 插入T的右子树 */
        T->Right = Insert(T->Right, X);
        /* 如果需要右旋 */
        if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
            if (X > T->Right->Data)
                T = SingleRightRotation(T); /* 右单旋 */
            else
                T = DoubleRightLeftRotation(T); /* 右-左双旋 */
    }                                           /* else if (插入右子树) 结束 */

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}
// 求二叉树的高度。
int GetHeight(AVLTree BT)
{
    int HL, HR, MaxH;
    if (BT)
    {
        HL = GetHeight(BT->Left);   /*求左子树的深度*/
        HR = GetHeight(BT->Right);  /*求右子树的深度*/
        MaxH = (HL > HR) ? HL : HR; /*取左右子树较大的深度*/
        return (MaxH + 1);          /*返回树的深度*/
    }
    else
        return 0; /* 空树深度为0 */
}
//输入
// 7
// 88 70 61 96 120 90 65
//输出
// 88
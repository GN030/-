//层序遍历：遍历从根节点开始，首先将根节点入队，然后执行循环：结点出队、访问该结点、其左右儿子入队
#include <stdio.h>
#include <stdlib.h>
#define ElementType BinTree
#define ERROR 0
typedef struct TreeNode *BinTree;
struct TreeNode
{
    int Data;
    BinTree Left;
    BinTree Right;
};

void LevelOrderTraversal(BinTree BT); //二叉树层序遍历的实现
// 01层序遍历：根结点入队；
//从队列中取出一个元素；访问该元素所指向的结点；
//若该元素所指结点的左右孩子结点非空，将其左右孩子结点的指针顺序入队。
void LevelOrderTraversal(BinTree BT)
{
    Queue Q;
    BinTree T;
    if (!BT) //若是空树，直接返回
        return;
    Q = CreatQueue(MaxSize); //创建并初始化队列Q
    AddQ(Q, BT);
    while (!IsEmptyQ(Q))
    {
        T = DeleteQ(Q);
        printf("%d\n", T->Data);
        if (T->Left)
            AddQ(Q, T->Left);
        if (T->Right)
            AddQ(Q, T->Right);
    }
}
// 02.输出二叉树中的叶子节点：在遍历算法中，增加检测结点的左右子树是否为空，若空，打印该结点。
void PreOrderPrintLeaves(BinTree BT)
{
    if (BT)
    {
        if (!BT - Left && !BT->Right)
            printf(“% d”, BT->Data);
        PreOrderPrintLeaves(BT->Left);
        PreOrderPrintLeaves(BT->Right);
    }
}
// 03.求二叉树的高度。
int PostOrderGetHeight(BinTree BT)
{
    int HL, HR, MaxH;
    if (BT)
    {
        HL = PostOrderGetHeight(BT->Left);  /*求左子树的深度*/
        HR = PostOrderGetHeight(BT->Right); /*求右子树的深度*/
        MaxH = (HL > HR) ? HL : HR;         /*取左右子树较大的深度*/
        return (MaxH + 1);                  /*返回树的深度*/
    }
    else
        return 0; /* 空树深度为0 */
}
//03.由两种遍历序列唯一确定一颗二叉树：必须要有中序遍历
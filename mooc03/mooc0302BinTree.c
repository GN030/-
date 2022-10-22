//二叉树的存储实现Binary Tree
//相较于顺序存储，链式存储更节约空间；顺序存储比较适合完全二叉树，且父节点、结点左孩子、结点右孩子之间存在一定的序号关系,对于一般二叉树而言，会造成比较大的空间浪费。

#include <stdio.h>
#include <stdlib.h>
#define ElementType BinTree
#define ERROR 0
// 01.二叉树链式存储的实现
typedef struct TreeNode *BinTree;
struct TreeNode
{
    int Data;
    BinTree Left;
    BinTree Right;
};
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    Stack Next;
};
Stack CreatStack();
int IsEmpty(Stack S);
void Push(Stack S, ElementType item);
ElementType Pop(Stack S);
void PreOrderTraversal(BinTree BT);
void InOrderTraversal(BinTree BT);
void PostOrderTraversal(BinTree BT);
void PreOrderTraversal_Stack(BinTree BT);
void InOrderTraversal_Stack(BinTree BT);
void PostOrderTraversal_Stack(BinTree BT);
//创建一个二叉树,用于测试:1;2,4;5 NULL NULL 3;
//先序访问结果：1，2，5，4，3；中序访问结果：5，2，1，4，3；后序访问结果：5，2，3，4，1；
int main(void)
{
    BinTree BT, temp1, temp2, temp3, temp4, temp5, temp6;
    temp1 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp2 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp3 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp4 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp5 = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    BT = temp1;
    temp1->Data = 1;
    temp1->Left = temp2;
    temp1->Right = temp3;
    temp2->Data = 2;
    temp2->Left = temp4;
    temp2->Right = NULL;
    temp3->Data = 4;
    temp3->Left = NULL;
    temp3->Right = temp5;
    temp4->Data = 5;
    temp4->Left = NULL;
    temp4->Right = NULL;
    temp5->Data = 3;
    temp5->Left = NULL;
    temp5->Right = NULL;
    printf("先序访问结果：1，2，5，4，3；\n");
    PreOrderTraversal(BT);
    printf("\n");
    PreOrderTraversal_Stack(BT);
    printf("\n");
    printf("中序访问结果：5，2，1，4，3；\n");
    InOrderTraversal(BT);
    printf("\n");
    InOrderTraversal_Stack(BT);
    printf("\n");
    printf("后序访问结果：5，2，3，4，1；\n");
    PostOrderTraversal(BT);
    printf("\n");
    PostOrderTraversal_Stack(BT);
    printf("\n");
    while (1)
        ;
    system("pause");
}
// 02.先序遍历：先访问根节点，先序遍历其左子树，先序遍历其右子树。
void PreOrderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d", BT->Data);
        PreOrderTraversal(BT->Left);
        PreOrderTraversal(BT->Right);
    }
}
// 03.中序遍历：中序遍历其左子树，访问根节点，中序遍历其右子树
void InOrderTraversal(BinTree BT)
{
    if (BT)
    {
        InOrderTraversal(BT->Left);
        printf("%d", BT->Data);
        InOrderTraversal(BT->Right);
    }
}
// 04.后序遍历：后序遍历其左子树，后序遍历其右子树，访问根节点
void PostOrderTraversal(BinTree BT)
{
    if (BT)
    {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        printf("%d", BT->Data);
    }
}
// 05.堆栈实现中序遍历：遇到一个结点把它压入堆栈，去遍历左子树；
//左子树遍历结束，从栈顶弹出该结点，访问它；接下来再用中序遍历其右子树。
void InOrderTraversal_Stack(BinTree BT)
{
    BinTree T = BT;
    Stack S = CreatStack(); //创建并初始化堆栈S
    while (T || !IsEmpty(S))
    {
        while (T) //一直向左，并将沿途结点压入堆栈
        {
            Push(S, T);
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            printf("%d", T->Data); //打印结点
            T = T->Right;          //转向右子树
        }
    }
}
// 06.堆栈实现先序遍历：遇到一个结点，访问它，并把它压入堆栈，去遍历左子树；
//左子树遍历结束，从栈顶弹出该结点；接下来再用先序遍历其右子树。
void PreOrderTraversal_Stack(BinTree BT)
{
    BinTree T = BT;
    Stack S = CreatStack(); //创建并初始化堆栈S
    while (T || !IsEmpty(S))
    {
        while (T) //一直向左，并将沿途结点压入堆栈
        {
            printf("%d", T->Data); //打印结点
            Push(S, T);
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            T = T->Right; //转向右子树
        }
    }
}
// 07.堆栈实现后序遍历：遇到一个结点，并把它压入堆栈，去后序遍历左子树；
//左子树遍历结束，从栈顶弹出该结点，判断是否有右子树；
//若无右子树，访问该结点；若有右子树，再用后序遍历其右子树；
//对于一个小树，遇到父结点，将其压入堆栈，去遍历他的左子结点压入堆栈；
//下一左子结点不存在时，若有下一右子节点，将其压入堆栈，并指向右子结点，继续去遍历他的左子结点，并压入堆栈；
//若下一左子结点和下一右子结点都不存在，访问该子结点；此时要访问该子结点的父结点，弹出父结点并访问。
void PostOrderTraversal_Stack(BinTree BT)
{
    BinTree T = BT, pre; // pre存储最近访问的结点
    pre = -1;
    Stack S = CreatStack(); //创建并初始化堆栈S
    while (T || !IsEmpty(S))
    {
        while (T && pre != T->Left && pre != T->Right && pre != T) //一直向左，将沿途结点（未被访问）压入堆栈
        {
            Push(S, T);
            T = T->Left;
        }
        if (!IsEmpty(S))
        {
            T = Pop(S);
            if (!T->Right)
            {
                printf("%d", T->Data);
                pre = T;
            }
            else if (T->Right && pre == T->Right)
            {
                printf("%d", T->Data);
                pre = T;
            }
            else
            {
                Push(S, T);
                T = T->Right; //转向右子树}
            }
        }
    }
}
//堆栈初始化（建立空栈）
/*注意这里创建的是一个带头结点链式堆栈，还存在无头节点的形式*/
Stack CreatStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
//判断堆栈S是否为空,若为空返回整数1，否则返回0
int IsEmpty(Stack S)
{
    return (S->Next == NULL);
}
// 02.入栈
void Push(Stack S, ElementType item)
{
    Stack TmpCell;
    TmpCell = (Stack)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}
// 03.出栈
ElementType Pop(Stack S)
{
    Stack FirstCell;
    BinTree TopElem;
    if (S->Next == NULL)
    {
        printf("堆栈空");
        return ERROR;
    }
    else
    {
        FirstCell = S->Next;
        S->Next = FirstCell->Next;
        TopElem = FirstCell->Data;
        free(FirstCell);
        return TopElem;
    }
}
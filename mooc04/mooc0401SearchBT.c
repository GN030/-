#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct TreeNode *BinTree;
struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
// 01二叉搜索树的查找操作Find(递归实现)
BinTree Find(ElementType X, BinTree BST)
{
    if (!BST)
        return NULL;
    if (X > BST->Data)
        return Find(X, BST->Right); //在右子树中继续查找
    else if (X < BST->Left)
        return Find(X, BST->Left); //在左子树中继续查找
    else
        return BST; //查找成功，返回结点的找到结点的地址
}
// 02二叉搜索树的查找操作Find(迭代实现)
BinTree IterFind(ElementType X, BinTree BST)
{
    while (BST)
    {
        if (X > BST->Data)
            BST = BST->Right; //向右子树中移动，继续查找
        else if (X < BST->Data)
            BST = BST->Left; //向左子树中移动，继续查找
        else
            return BST; //查找成功，返回结点的找到结点的地址
    }
    return NULL; //查找失败
}
// 03二叉搜索树递归查找最小元素
BinTree FindMin(BinTree BST)
{
    if (!BST)
        return NULL; //空树，返回NULL
    else if (!BST->Left)
        return BST;
    else
        return FindMin(BST->Left);
}
// 04二叉搜索树迭代查找最小元素
BinTree IterFindMin(BinTree BST)
{
    if (BST)
        while (BST->Left)
            BST = BST->Left;
    return BST;
}
// 05插入元素
BinTree Insert(ElementType X, BinTree Pstr)
{
    if (!Pstr) //如果结点为空，则申请空间存放要插入的元素X
    {
        Pstr = (BinTree)malloc(sizeof(struct TreeNode));
        Pstr->Data = X;
        Pstr->Left = NULL;
        Pstr->Right = NULL;
    }
    //开始插入元素，X插入左子树，X插入右子树，X已经存在
    else if (X < Pstr->Data)
        Pstr = Insert(X, Pstr->Left);
    else if (X > Pstr->Right)
        Pstr = Insert(X, Pstr->Right);
    return Pstr;
}
// 06二叉搜索树删除元素：情况1删除叶结点，直接删除，修改父结点指针；情况2删除只有一个孩子的结点，将其父结点指向该结点的孩子结点；
//情况3删除有两个孩子的结点，搜索其左子树的最大元素或右子树的最小元素，替代要删除的结点元素，并在左子树中删除该元素。
BinTree Delete(ElementType X, BinTree BST)
{
    BinTree temp;
    if (!BST)
        printf("该元素不存在");
    else if (X < BST->Data)
        Delete(X, BST->Left); //左子树递归删除
    else if (X > BST->Data)
        Delete(X, BST->Right); //右子树递归删除
    //找到要删除的结点元素
    else if (BST->Left && BST->Right) //情况3左右子树都存在
    {
        temp = FindMin(BST->Right); //找到右子树中的最小元素
        BST->Data = temp->Data;
        BST->Right = Delete(temp->Data, BST->Right); //在右子树中删除该结点元素
    }
    else
    {
        temp = BST->Right;
        if (!BST->Left) //情况2没有左子树（只有右子树或没有子树）
        {
            // BST->Data = BST->Right->Data;
            // BST->Left = BST->Right->Left;
            // BST->Right = BST->Right->Right;
            //不能这样用，BST指针存储当前要删除的结点的地址，而父结点保存的是当前结点的指针地址变量，即BST；
            // 故可以直接更改BST指针所保存的内容，来实现更改删除该结点。
            BST = BST->Right;
        }
        else if (!BST->Right) //情况2只有左子树
        {
            BST = BST->Left;
        }
        free(temp);
    }
    return BST;
}
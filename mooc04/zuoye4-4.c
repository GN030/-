//二叉搜索树5种常用操作的实现
// 01插入元素
BinTree Insert(BinTree BST,ElementType X)
{
    if (!BST) //如果结点为空，则申请空间存放要插入的元素X
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    //开始插入元素，X插入左子树，X插入右子树，X已经存在
    else if (X < BST->Data)
        BST->Left = Insert(BST->Left, X);
    else if (X > BST->Data)
        BST->Right = Insert(BST->Right, X);
    return BST;
}
// 02二叉搜索树删除元素：情况1删除叶结点，直接删除，修改父结点指针；情况2删除只有一个孩子的结点，将其父结点指向该结点的孩子结点；
//情况3删除有两个孩子的结点，搜索其左子树的最大元素或右子树的最小元素，替代要删除的结点元素，并在左子树中删除该元素。
BinTree Delete(BinTree BST,ElementType X)
{
    BinTree temp;
    if (!BST)
        printf("Not Found\n");
    else if (X < BST->Data)
        BST->Left=Delete(BST->Left, X); //左子树递归删除
    else if (X > BST->Data)
        BST->Right=Delete(BST->Right, X); //右子树递归删除
    //找到要删除的结点元素
    else if (BST->Left && BST->Right) //情况3左右子树都存在
    {
        temp = FindMin(BST->Right); //找到右子树中的最小元素
        BST->Data = temp->Data;
        BST->Right = Delete(BST->Right, temp->Data); //在右子树中删除该结点元素
    }
    else
    {
        temp = BST;
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
// 03查找操作Find(递归实现)
Position Find(BinTree BST,ElementType X)
{
    if (!BST)
        return NULL;
    if (X > BST->Data)
        return Find(BST->Right,X); //在右子树中继续查找
    else if (X < BST->Data)
        return Find(BST->Left,X); //在左子树中继续查找
    else
        return BST; //查找成功，返回结点的找到结点的地址
}
// 04递归查找最小元素
Position FindMax(BinTree BST)
{
    if (!BST)
        return NULL; //空树，返回NULL
    else if (!BST->Right)
        return BST;
    else
        return FindMax(BST->Right);
}
// 05递归查找最小元素
Position FindMin(BinTree BST)
{
    if (!BST)
        return NULL; //空树，返回NULL
    else if (!BST->Left)
        return BST;
    else
        return FindMin(BST->Left);
}


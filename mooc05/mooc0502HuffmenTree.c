/*哈夫曼树：带权路径长度WPL最小的二叉树*/
/*建立方法：首先将所有元素建立一个完全二叉树，采用顺序存储，Elements每个元素采用哈夫曼结点的结构，一个Element包含权值Weight，左右哈夫曼子树默认为NULL*/
/*将完全二叉树建立为最小堆;每次删除两个最小堆堆顶元素，设计一个新哈夫曼结点指向这两个堆顶元素，并计算新哈夫曼结点的权重，将新哈弗曼结点插入最小堆中*/
/*一共要做H->Size-1次合并，最后最小堆只剩一个堆顶元素，删除最小堆操作返回一个哈夫曼树的根节点指针*/
#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode *HuffmanTree;
struct TreeNode
{
    int Weight;
    HuffmanTree Left, Right;
};
HuffmanTree Huffman(MinHeap H)
{ /*H是一个完全二叉树，假设H->size个权值已经存放在H->Elements[]->Weight里*/
    int i;
    HuffmanTree T;
    BuildMinHeap(H); /*将H->Elements[]按权值调整为最小堆*/
    for(i=1;i<H->Size;i++)
    {/*做H->Size-1次合并*/
        T=(HuffmanTree)malloc(sizeof(struct TreeNode));
        T->Left=DeleteMin(H);
        /*从最小堆中删除一个结点，作为新T的右子结点*/
        T->Right=DeleteMin(H);
        /*从最小堆中删除一个结点，作为新T的右子结点*/
        T->Weight=T->Left->Weight+T->Right->Weight;
        /*计算新权值*/
        Insert(H,T);/*将新T插入到最小堆*/
    }
    T=DeletMin(H);
    return T;
}

//题中给出的堆栈操作指令，其中Push对应二叉树先序遍历结果，Pop对应二叉树中序遍历结果；要求实现二叉树的后序遍历输出
//操作注意：scanf输入一个数据后，注意匹配回车键，否则回车符会保存在缓冲区，影响下一个键盘输入，尤其是输入为字符串或者字符时。
#include <stdio.h>
#include <stdlib.h>
// #include <cstring>
#define ElementType int
#define MaxSize 31
#define ERROR -1
int idx=0;
int Post[MaxSize+1];//存储后序遍历的输出结果
int PreOrder[MaxSize], InOrder[MaxSize]; //保存二叉树先序和中序遍历结果
//二叉树的链式存储
typedef struct TreeNode *TNode;
struct TreeNode
{
    ElementType Data;
    TNode Left;
    TNode Right;
};
//堆栈的顺序存储
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data[MaxSize];
    int Top;
} S1;
TNode BuildTree(int PreL, int PreR, int InL, int InR); //建立二叉树（采用链式存储结构）
void Push(Stack PtrS, ElementType item);               //入栈
ElementType Pop(Stack PtrS);                           //出栈
void PostOrderTraversal(TNode BT);                     //后序遍历
int main(void)
{
    //接收输入
    int nums, i, j, k, data,item; // nums二叉树结点个数
    i = 0;
    j = 0;
    char Str[5]; //输入的命令,要预留一个元素位置保存空格
    scanf("%d\n", &nums);
    if (nums) //二叉树非空
    {
        for (k = 0; k < (2 * nums); k++) //接收输入
        {
            Str[0]=getchar();
            Str[1]=getchar();
            Str[2]=getchar();
            Str[5]='\0';
            if (Str[0] == 'P' && Str[1] == 'u')
            {
                Str[3]=getchar();
                Str[4]=getchar();
                scanf("%d",&data);/*注意，这里要输入一个数字，不可以再用getchar，否则导致无法读取数字十位及以上部分*/
                getchar();//处理缓冲区的回车符
                // printf("Str:%s Data:%d\n", Str, data);
                PreOrder[i++] = data;
                Push(&S1, data);
            }
            else // Pop操作
            {
                getchar();//处理缓冲区的回车符
                // printf("Str:%s\n", Str);
                InOrder[j++] = Pop(&S1);
            }
        }
    }
    TNode BT = BuildTree(0, nums - 1, 0, nums - 1);
    PostOrderTraversal(BT);
    for(i=0;i<idx-1;i++)
    printf("%d ",Post[i]);
    printf("%d",Post[idx-1]);
    return 0;
}
//建立二叉树,先找根结点，确定根节点左右子树的序号区间，然后通过递归找左右子结点，返回根结点地址
//先序遍历：根结点-左子树-右子树；
//中序遍历：左子树-根结点-右子树；
TNode BuildTree(int PreL, int PreR, int InL, int InR)
{
    if (PreL > PreR)
        return NULL;
    int k; //根节点在中序遍历中的序号
    TNode Root = (TNode)malloc(sizeof(struct TreeNode));
    Root->Data = PreOrder[PreL];
    for (int i = InL; i <= InR; i++)
    {
        if (Root->Data == InOrder[i])
        {
            k = i;
            break;
        }
    }
    int Leftnum = k - InL;
    Root->Left = BuildTree(PreL + 1, PreL + Leftnum, InL, k - 1);
    Root->Right = BuildTree(PreL + Leftnum + 1, PreR, k + 1, InR);
    return Root;
}
void Push(Stack PtrS, ElementType item)
{ //入栈
    if (PtrS->Top == MaxSize)
    {
        printf("堆栈满\n");
        return;
    }
    else
    {
        PtrS->Top++;
        PtrS->Data[PtrS->Top] = item;
        return;
    }
}
ElementType Pop(Stack PtrS)
{ //出栈
    if (PtrS->Top == -1)
    {
        printf("堆栈空\n");
        return ERROR;
    }
    else
        return (PtrS->Data[(PtrS->Top)--]);
}
void PostOrderTraversal(TNode BT)
{
    if (BT)
    {
        PostOrderTraversal(BT->Left);
        PostOrderTraversal(BT->Right);
        Post[idx++]=BT->Data;
    }
}
/*N=30，测试
30
Push 1
Push 2
Push 3
Push 4
Push 5
Push 6
Push 7
Push 8
Push 9
Push 10
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Push 11
Push 12
Push 13
Push 14
Push 15
Push 16
Push 17
Push 18
Push 19
Push 20
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Push 21
Push 22
Push 23
Push 24
Push 25
Push 26
Push 27
Push 28
Push 29
Push 30
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
Pop
*/
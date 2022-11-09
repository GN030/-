/*Tree Traversals Again:给定Push和Pop操作,Push对应中序遍历.Pop对应后序遍历序列,根据递归程序生成后序遍历*/
/*老师思路:先序遍历:根结点+左子树+右子树;中序遍历:左子树+根结点+右子树;后序遍历:左子树+右子树+根结点
1,首先将先序遍历根结点pre[preL]存入后序遍历post[postL+n-1],然后根据根结点在中序遍历中的序号inL+i;
2,确定左子树[preL+1,inL,postL,L=i],和右子树[preL+1+L,inL+L+1,postL+L,R=n-L-1]
3,解决临界点:n=0;n=1;
*/
#include <stdio.h>
#include <stdlib.h>
#define Maxsize 100
int in[Maxsize], pre[Maxsize], post[Maxsize];
/*堆栈的链式存储*/
#define ElementType int
#define ERROR 0
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    Stack Next;
};

/*堆栈的函数声明*/
Stack CreateStack();
int IsEmpty(Stack S);
void Push(Stack S, ElementType item); //入栈
ElementType Pop(Stack S);             //出栈

void solve(int preL, int inL, int postL, int n);

int main(void)
{
    Stack S;
    S = CreateStack();
    int N, i, p, q;
    p = 0;
    q = 0;
    char a[4];
    scanf("%d", &N);
    getchar();
    for (i = 0; i < 2 * N; i++)
    {
        a[0] = getchar();
        a[1] = getchar();
        a[2] = getchar();
        if (a[0] == 'P' && a[1] == 'u')
        {
            getchar();
            getchar();              /*Push+空格*/
            scanf("%d", &pre[p++]); /*对应的是先序遍历*/
            Push(S, pre[p - 1]);
            getchar(); /*回车符*/
        }
        else if (a[0] == 'P' && a[1] == 'o')
        {
            in[q++] = Pop(S); /*对应的是中序遍历*/
            getchar();        /*回车符*/
        }
        else
            printf("输入错误\n");
    }
    solve(0, 0, 0, N);

    /*打印*/
    for (i = 0; i < N - 1; i++)
    {
        printf("%d ", post[i]);
    }
    printf("%d\n", post[i]);

    return 0;
}
void solve(int preL, int inL, int postL, int n)
{
    int root, i, L, R;
    /*解决临界点*/
    if (n == 0)
        return;
    if (n == 1)
    {
        post[postL] = pre[preL];
        return;
    }
    root = pre[preL];           /*保存根结点*/
    post[postL + n - 1] = root; /*将根结点放到后序遍历序列中,位置在当前子树的最后一个位置*/
    for (i = 0; i < n; i++)     /*在中序遍历序列中寻找根结点的下标*/
        if (in[inL + i] == root)
            break;
    L = i;                                          /*左子树的结点数*/
    R = n - L - 1;                                  /*右子树的结点数*/
    solve(preL + 1, inL, postL, L);                 /*解决左子树,先序遍历preL+1,中序遍历inL,后序遍历postL,树的结点数L*/
    solve(preL + L + 1, inL + L + 1, postL + L, R); /*解决右子树,先序遍历preL+1+L,中序遍历inL+L+1,后序遍历postL+L,树的结点数L*/
}
//堆栈初始化（建立空栈）
/*注意这里创建的是一个带头结点链式堆栈，还存在无头节点的形式*/
Stack CreateStack()
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
    ElementType TopElem;
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
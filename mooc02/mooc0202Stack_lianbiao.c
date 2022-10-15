//堆栈的链表存储实现
//01.存储实现
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define ERROR 0
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    Stack Next;
};
Stack CreateStack();
int IsEmpty(Stack S);

int main(void)
{
    Stack S;
    S = CreateStack();
    IsEmpty(S);
    return 0;
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
//02.入栈
void Push(Stack S,ElementType item)
{
    Stack TmpCell;
    TmpCell = (Stack)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}
//03.出栈
ElementType Pop(Stack S)
{
    Stack FirstCell;
    ElementType TopElem;
    if (S->Next==NULL)
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
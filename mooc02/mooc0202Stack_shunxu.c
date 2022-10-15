//堆栈的顺序存储实现
//01.存储实现
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MaxSize 10
#define ERROR 0
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data[MaxSize];
    int Top;
};

int main(void)
{
    return 0;
}
//02.入栈
void Push(Stack PtrS,ElementType item)
{
    if(PtrS->Top==MaxSize)
    {
        printf("堆栈满");
        return;
    }
    else
    {
        PtrS->Top++;
        PtrS->Data[PtrS->Top] = item;
        return;
    }
}
//03.出栈
ElementType Pop(Stack PtrS)
{
    if (PtrS->Top==-1)
    {
        printf("堆栈空");
        return ERROR;
    }
    else
    return(PtrS->Data[(PtrS->Top)--]);
}
//队列的顺序存储实现
//01.存储实现
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MaxSize 10
typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MaxSize];
    int rear;//记录尾元素序号
    int front;//记录头元素序号
};

int main(void)
{
    struct QNode Q;
}
//02.入队列，队列采用循环结构可以最大限度利用空间
void AddQ(Queue PtrQ,ElementType item)
{
    if((PtrQ->rear+1)%MaxSize==PtrQ->front)
    {
        printf("队列满");
        return;
    }
    PtrQ->rear = (PtrQ->rear+1)%MaxSize;
    PtrQ->Data[PtrQ->rear] = item;
}
//03.出队列
ElementType DeleteQ(Queue PtrQ)
{
    ElementType item;
    if(PtrQ->front==PtrQ->rear)
    {
        printf("队列空");
        return;
    }
    PtrQ->front = (PtrQ->front+1)%MaxSize;
    return (PtrQ->Data[PtrQ->front]);
}
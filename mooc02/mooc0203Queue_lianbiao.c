//队列的链表存储实现
//01.存储实现
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct QNode *Queue;
struct Node
{
    ElementType Data;
    struct Node *Next;
};
/*这里采用链队列结构，用于指示队头和队尾。*/
struct QNode
{
    struct Node *rear;//指向队尾的节点
    struct Node *front;//指向队头的节点
};
int main(void)
{
    Queue PtrQ;
    return 0;
}
//02.入队操作
void AddQ(Queue PtrQ,ElementType item)
{
    struct Node *TempCell;
    TempCell = (struct Node*)malloc(sizeof(struct Node));
    TempCell->Data = item;
    PtrQ->rear->Next = TempCell;
    PtrQ->rear = TempCell;
}
//03.出队操作
ElementType DeleteQ(Queue PtrQ)
{
    struct Node *TempCell;
    ElementType item;
    if(PtrQ->front==NULL)
    {
        printf("队列空");
        return 0;
    }
    TempCell = PtrQ->front;
    if(PtrQ->front==PtrQ->rear)
    {
        printf("队列只有一个元素");
        PtrQ->front = NULL;
        PtrQ->rear = NULL;
    }
    PtrQ->front = TempCell->Next;
    item = TempCell->Data;
    free(TempCell);
    return item;
}

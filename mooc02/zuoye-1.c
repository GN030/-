#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

/* 你的代码将被嵌在这里 */
List Merge(List L1, List L2)
{
    List P, prear, temp;
    P = (List)malloc(sizeof(struct Node));
    P->Next = NULL;
    prear = P; //链表的末尾
    while (L1->Next && L2->Next)
    {
        if (L1->Next->Data > L2->Next->Data) //若L1数据>L2数据，将该节点连接到结果链表P上，并使L1继续指向该节点的下一节点
        {
            temp = L1->Next;
            L1->Next = temp->Next;
            prear->Next = temp;
            prear = temp;
        }
        else if (L1->Next->Data < L2->Next->Data) //若L1数据<L2数据，情况同上，对L2进行操作。
        {
            temp = L2->Next;
            L2->Next = temp->Next;
            prear->Next = temp;
            prear = temp;
        }
        else //若L1数据=L2数据，同时对L1和L2进行操作
        {
            temp = L1->Next;
            L1->Next = temp->Next;
            prear->Next = temp;
            prear = temp;
            temp = L2->Next;
            L2->Next = temp->Next;
            prear->Next = temp;
            prear = temp;
        }
    }
    //将L1或L2的剩余部分全部连接到结果末尾
    while (L1->Next)
    {
        temp = L1->Next;
        L1->Next = temp->Next;
        prear->Next = temp;
        prear = temp;
    }
    while (L2->Next)
    {
        temp = L2->Next;
        L2->Next = temp->Next;
        prear->Next = temp;
        prear = temp;
    }
    return P;
}
//检查方法：数123...i，输入序列L；
//如果堆栈为空，(i<=Length)向堆栈Push一个数i,i++;
//比较堆栈顶元素和L[j]的大小：相等，则堆栈Pop，j++;如果不相等，（检查堆栈是否满），Push数i，i++;
//如果堆栈已满，而L还未到末尾值，输出NO；如果堆栈未满，继续Push;
//若i>Length，输出NO；
//如果L末尾值与堆栈栈顶元素匹配，即i==j==Length，输出YES

#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct SNode *Stack;
struct SNode
{
    ElementType Data, NodeNum;
    Stack Next;
};
Stack CreateSnack();
int IsEmpty(Stack S);
void Push(Stack S, ElementType t);
ElementType Pop(Stack S);
int main(void)
{
    Stack S;
    S = CreateSnack();
    ElementType StackSize, Length, Num, i, j, k, w;
    scanf("%d %d %d", &StackSize, &Length, &Num);
    S->NodeNum = 0;
    int L[Num][Length], Result[Num];
    for (k = 0; k < Num; k++)
    {
        for (i = 0; i < Length; i++) //输入一行数据，存入数组L[];
            scanf("%d", &L[k][i]);
    }

    for (k = 0; k < Num; k++)
    {
        w = 0; //数组L[k][w]
        i = 1; //顺序数123...Length
        while(!IsEmpty(S))
        {
            Pop(S);
        }
        while (1)
        {
            if (IsEmpty(S))
            {
                if (i <= Length)
                {
                    // printf("空堆栈，Push操作");
                    Push(S, i);
                    i++;
                }
            }
            //比较栈顶元素与序列数L[i]
            if (S->Next->Data == L[k][w]) //相等，堆栈Pop，j++
            {
                Pop(S);
                w++;
            }
            else //不相等，(检查堆栈满没满)，继续Push
            {
                if (S->NodeNum == StackSize)
                {
                    Result[k] = 0;
                    break;
                    ;
                }
                else
                {
                    Push(S, i);
                    i++;
                }
            }
            //判断是否到达数123的末尾
            if (i > Length + 1) //数123已经全部送进堆栈，NO
            {
                Result[k] = 0;
                break;
                ;
            }
            if (i == Length + 1 && w == Length) //数123和L[k]匹配，YES
            {
                Result[k] = 1;
                break;
            }
        }
    }
    //输出判断结果
    for (i = 0; i < Num; i++)
    {
        if (Result[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
    while (1)
        ;
    return 0;
}
Stack CreateSnack()
{ //创建空堆栈，带头结点形式,返回堆栈头节点地址
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
int IsEmpty(Stack S)
{ //判断堆栈是否为空，空返回1，非空返回0
    if (S->Next == NULL)
        return 1;
    else
        return 0;
}
void Push(Stack S, ElementType t)
{ //入栈
    Stack temp;
    temp = (Stack)malloc(sizeof(struct SNode));
    temp->Data = t;
    temp->Next = S->Next;
    S->Next = temp;
    S->NodeNum++;
}
ElementType Pop(Stack S)
{ //出栈
    Stack FirstCell;
    ElementType TopElem;
    if (S->Next == NULL)
    {
        printf("堆栈空");
        return -1;
    }
    else
    {
        FirstCell = S->Next;
        S->Next = FirstCell->Next;
        TopElem = FirstCell->Data;
        free(FirstCell);
        S->NodeNum--;
        return TopElem;
    }
}

/*题目介绍：输入计算机数目N，C i j表示查询第i台和第j台计算机是否连接；I i j表示连接第i台和第j台计算机；
S表示输入结束，若计算机以全部连接，打印“The network is connected.”，否则打印“There are m components.”，其中m表示计算机集合个数*/
/*思路：1.使用集合的简化表示（使用数组来存储集合，数组下标对应元素值，数组值对应根结点元素下标）
2.集合查找时选用路径压缩的方法（将每一个元素都调整为指向根结点）注意：将N台计算机映射到集合0-(N-1)范围
3.集合并操作选用按秩归并的方法（层数，节点个数）*/
/*具体实现见下文代码*/

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10001
/*集合的简化表示：将有限集合的N个元素映射到整数0-(N-1)，集合元素用下标来表示，其存储的内容为对应的父结点下标*/
typedef int ElementType; /*默认元素可以用非负整数表示*/
typedef int SetName;     /*默认用根结点的下标作为集合名称*/
typedef ElementType SetType[MaxSize];

void Input_connection(SetType S);     /*连接两台计算机*/
void Check_connection(SetType S);     /*检查两台计算机是否连接*/
void Check_network(SetType S, int N); /*检查整个计算机网络*/
SetName Find(SetType S, ElementType X);
void Union(SetType S, SetName Root1, SetName Root2);
// Initialization(SetType S, int N);
int main(void)
{
    SetType S;
    int N, i;
    char Comd;
    /*初始化集合*/
    scanf("%d", &N);
    getchar();
    for (i = 0; i < N; i++)
        S[i] = -1;
    do
    {
        Comd = getchar();
        switch (Comd)
        {
        case 'I': /*连接两台计算机*/
            Input_connection(S);
            break;
        case 'C': /*检查两台计算机是否连接*/
            Check_connection(S);
            break;
        case 'S': /*检查整个计算机网络*/
            Check_network(S, N);
            break;
        }
    } while (Comd != 'S');
    return 0;
}
void Input_connection(SetType S)
{ /*连接两台计算机*/
    ElementType m1, m2;
    SetName Root1, Root2;
    scanf("%d%d", &m1, &m2);
    getchar();
    Root1 = Find(S, m1 - 1);
    Root2 = Find(S, m2 - 1);
    if (Root1 != Root2) /*将两台计算机的根结点连接起来*/
        Union(S, Root1, Root2);
}
void Check_connection(SetType S)
{ /*检查两台计算机是否连接*/
    ElementType m1, m2;
    SetName Root1, Root2;
    scanf("%d%d", &m1, &m2);
    getchar();
    Root1 = Find(S, m1 - 1);
    Root2 = Find(S, m2 - 1);
    if (Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
}
void Check_network(SetType S, int N)
{ /*检查整个计算机网络*/
    int i, counter = 0;
    for (i = 0; i < N; i++)
    {
        if (S[i] < 0)
            counter++;
    }
    if (counter == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.", counter);
}
SetName Find(SetType S, ElementType X)
{ /*默认集合元素全部初始化为-1*/
    /*路径压缩*/
    if (S[X] < 0)
        return X;
    else
        return S[X] = Find(S, S[X]); /*递归：遇到根结点时，返回根结点下标X2，将X2赋值给上一个结点S[X1]=X2,并继续返回X1*/
}
void Union(SetType S, SetName Root1, SetName Root2)
{ /* 这里默认Root1和Root2是不同集合的根结点 */
    /*按秩归并：元素个数*/
    if (S[Root1] < S[Root2])
    { /*树1元素更多一些，将集合2指向集合1*/
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
    else
    { /*树2元素更多一些，将集合1指向集合2*/
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    // /*按秩归并：树高*/
    // if (S[Root1] < S[Root2])
    //     S[Root2] = Root1;
    // else
    // {
    //     if (S[Root1 == Root2])
    //         S[Root2]--; /*树高相同时，将集合1指向集合2*/
    //     S[Root1] = Root2;
    // }
}
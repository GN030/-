#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MaxSize 100 /*数组的最大长度*/
typedef struct
{
    ElementType Data;
    int Parent
} SetType;
// 01查找某个元素所在的集合（用根节点表示）
int Find(SetType S[], ElementType X)
{ /*在数组s中查找值为X的元素所属的集合*/
    int i;
    for (i = 0; i < MaxSize && S[i].Data != X; i++)
    {
        if (i >= MaxSize)
            return -1; /*未找到X，返回-1*/
    }
    for (; S[i].Parent >= 0; i = S[i].Parent)
        ;
    return i; /*找到了X所属集合，返回树根节点在数组S中的下标*/
}
// 02集合的并运算
void Union(SetType S[], ElementType X1, ElementType X2)
{
    int Root1, Root2;
    Root1 = Find(S, X1);
    Root2 = Find(S, X2);
    if (Root1 != Root2) /*保证不是同一个集合*/
    {
        if (S[Root1].Parent >= S[Root2].Parent) /*集合1更大，将集合2合并到集合1中，以优化集合结构，提高Find函数的效率*/
        {
            S[Root1].Parent += S[Root2].Parent;
            S[Root2].Parent = Root1;
        }
        else /*集合1小于集合2的情况*/
        {
            S[Root2].Parent += S[Root1].Parent;
            S[Root1].Parent = Root2;
        }
    }
}
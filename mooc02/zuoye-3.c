#include <stdio.h>
#include <stdlib.h>
#define NULL -1
#define MaxSize 100000
// typedef struct ListNode *LNode;
struct ListNode
{
    int Address;
    int Data;
    int NextAddress;
} L[MaxSize]; //定义一个数组链表
int main(void)
{
    //输入链表
    int i, j, FirstAdd, N, K, Knum;
    scanf("%d%d%d", &FirstAdd, &N, &K);
    for (i = 0; i < N; i++)
    {
        scanf("%d%d%d", &L[i].Address, &L[i].Data, &L[i].NextAddress);
    }
    L[N].Address = NULL;
    //按照所输入的数据地址对链表进行排序
    struct ListNode t1, t2; //
    for (i = 0; i < N; i++)
    {
        for (j = i; j < N; j++)
        {
            if (L[j].Address == FirstAdd)
            {
                FirstAdd = L[j].NextAddress;
                t1 = L[i];
                L[i] = L[j];
                L[j] = t1;
                break;
            }
        }
        if (FirstAdd == NULL) //判断是否到链表结尾,已排除有多余结点不在链表上的情况
        {
            N = i + 1;
        }
    }
    //按照K个间隔进行倒序处理
    Knum = N / K;
    // printf("%d", Knum);
    for (i = 0; i < Knum; i++)
    {
        for (j = 0; j < (K / 2); j++)
        {
            t1 = L[i * K + j];
            L[i * K + j] = L[i * K + K - j - 1];
            L[i * K + K - j - 1] = t1;
        }
    }
    //更新前N-1个结点的NextAddress值,并输出
    for (i = 0; i < N - 1; i++)
    {
        L[i].NextAddress = L[i + 1].Address;
        printf("%05d %d %05d\n", L[i].Address, L[i].Data, L[i].NextAddress);
    }
    L[i].NextAddress = -1; //更新最后一个结点的NextAddress值
    printf("%05d %d %d\n", L[i].Address, L[i].Data, L[i].NextAddress);
    return 0;
}
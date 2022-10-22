//静态数组，二分查找的实现

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ElementType int
#define MaxSize 100

typedef struct StaticTable
{
    ElementType Length;
    ElementType Data[MaxSize];
} * StaTP;
int BinarySearch(StaTP Tbl, ElementType K);
int main(void)
{
    StaTP Table;
    int k,i;
    Table = (StaTP)malloc(sizeof(struct StaticTable));
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 90};
    for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        Table->Data[i] = a[i];
    }
    Table->Length = 10;
    scanf("%d", &k);
    if (BinarySearch(Table, k) == -1)
        printf("NoFound");
    else
        printf("The Serial number of %d:%d", k, BinarySearch(Table, k));
        while(1);
}

int BinarySearch(StaTP Tbl, ElementType K)
{
    //静态数组的二分查找实现
    //计算中间元素坐标，判断K与中间元素关系，并调整左右边界left，right；若left<=right，继续比较判断；
    //若K在该数组中存在，则最终K在mid在处取值。
    //若K在该数组中不存在，在判断过程中会出现left>right
    int left, right, mid, NoFound = -1;
    left = 1;            //初始左边界
    right = Tbl->Length; //初始右边界
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (K < Tbl->Data[mid])
            right = mid - 1;
        else if (K > Tbl->Data[mid])
            left = mid + 1;
        else
            return mid;
    }
    return NoFound;
}
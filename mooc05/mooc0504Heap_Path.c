#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MinData -10001

typedef struct HeapNode *HeapTree;
struct HeapNode
{
    ElementType *Elements; /*存储堆元素的数组指针*/
    int Size;              /*堆当前的元素个数*/
    int Capacity;          /*堆的最大容量*/
};
HeapTree CreateHeapMin(int Maxsize);          //创建最小堆
void InsertMin(HeapTree H, ElementType item); //最小堆的插入
int IsFull(HeapTree H);                       //判断堆是否满，满堆返回1
int IsEmpty(HeapTree H);                      //判断堆是否空，空堆返回1
int main(void)
{
    int N, M, item, i, j; /*N为插入堆中的元素个数，M为需要进行查找的元素个数*/
    HeapTree H;
    H = CreateHeapMin(1000); //创建一个空堆
    scanf("%d %d", &N, &M);
    // int R[M],Path[M];           /*存放被查找的元素,和查找路径上的元素*/
    for (i = 0; i < N; i++) /*输入N个元素，并插入到最小堆中*/
    {
        scanf("%d", &item);
        InsertMin(H, item);
    }
    for (i = 0; i < M; i++)
    {
        scanf("%d", &j);
        printf("%d", H->Elements[j]);
        while (j > 1)
        {
            j /= 2;
            printf(" %d", H->Elements[j]);
        }
        printf("\n");
    }
    return 0;
}
// 创建最小堆
HeapTree CreateHeapMin(int Maxsize) //创建容量为Maxsize的空堆
{
    HeapTree H = (HeapTree)malloc(sizeof(struct HeapNode));
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (Maxsize + 1));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0] = MinData; //定义哨兵
    return H;
}
void InsertMin(HeapTree H, ElementType item) //将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
{
    int i;
    if (IsFull(H))
    {
        printf("堆已满\n");
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2] > item; i = i / 2)
    {
        H->Elements[i] = H->Elements[i / 2]; //向下过滤比插入值小的结点
    }
    H->Elements[i] = item; // item的插入位置
}
int IsFull(HeapTree H) //判断堆是否满，满堆返回1
{
    return (H->Size == H->Capacity);
}
int IsEmpty(HeapTree H) //判断堆是否空，空堆返回1
{
    return (H->Size == 0);
}
/*期待输入*/
// 5 3
// 46 23 26 24 10
// 5 4 3
/*期待输出*/
// 24 23 10
// 46 23 10
// 26 10
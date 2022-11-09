//堆：1完全二叉树表示，2任一结点的元素值是其子树所有结点的最大值或最小值
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElementType int
#define MaxData 1000 //哨兵元素应大于或小于堆中所有可能的元素
#define MinData -10  //哨兵元素应大于或小于堆中所有可能的元素
#define ERROR -1     /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
// 01堆的存储表示:因为堆为完全二叉树结构，故可以使用顺序存储结构来表示。
typedef struct HeapStruct *HeapTree;
typedef HeapTree MaxHeap; /* 最大堆 */
typedef HeapTree MinHeap; /* 最小堆 */
struct HeapStruct
{
    ElementType *Elements; //存储堆元素的数组指针
    int Size;              //堆当前元素的个数
    int Capacity;          //堆的最大容量
};

/*堆的函数声明*/
int IsFull(HeapTree H); //判断堆是否满，满堆返回1
int IsEmpty(HeapTree H); //判断堆是否空，空堆返回1
HeapTree CreateHeapMax(int Maxsize); //02创建最大堆,容量为Maxsize的空堆
HeapTree CreateHeapMin(int Maxsize) ;//02创建最小堆,容量为Maxsize的空堆
void InsertMax(HeapTree H, ElementType item); //03最大堆的插入:将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
void InsertMin(HeapTree H, ElementType item); // 03最小堆的插入:将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
ElementType DeleteMax(HeapTree H); // 04最大堆的删除:从最大堆H中取出键值最大的元素，并删除该结点
ElementType DeleteMin(HeapTree H); //04最小堆的删除:从最小堆H中取出键值最小的元素，并删除该结点
void PercDownMax(HeapTree H, int p);/*建造最大堆-下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
void BuildHeapMax(HeapTree H);/*建造最大堆*/
void PercDownMin(HeapTree H, int p);/*建造最小堆-下滤*/
void BuildHeapMin(HeapTree H);/*建造最小堆*/

int main(void)
{

    return 0;
}

/*堆的实现函数*/
int IsFull(HeapTree H) //判断堆是否满，满堆返回1
{
    return (H->Size == H->Capacity);
}
int IsEmpty(HeapTree H) //判断堆是否空，空堆返回1
{
    return (H->Size == 0);
}
// 02创建最大堆
HeapTree CreateHeapMax(int Maxsize) //创建容量为Maxsize的空堆
{
    HeapTree H = (HeapTree)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (Maxsize + 1));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0] = MaxData; //定义哨兵
    return H;
}
// 02创建最小堆
HeapTree CreateHeapMin(int Maxsize) //创建容量为Maxsize的空堆
{
    HeapTree H = (HeapTree)malloc(sizeof(struct HeapStruct));
    H->Elements = (ElementType *)malloc(sizeof(ElementType) * (Maxsize + 1));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0] = MinData; //定义哨兵
    return H;
}
// 03最大堆的插入
void InsertMax(HeapTree H, ElementType item) //将元素item插入到最大堆H中，其中哨兵为H->ElementType[0]
{
    int i;
    if (IsFull(H))
    {
        printf("堆已满\n");
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2] < item; i = i / 2)
    {
        H->Elements[i] = H->Elements[i / 2]; //向下过滤比插入值小的结点
    }
    H->Elements[i] = item; // item的插入位置
}
// 03最小堆的插入
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
// 04最大堆的删除
ElementType DeleteMax(HeapTree H) //从最大堆H中取出键值最大的元素，并删除该结点
{                                 //方法：用最大堆中的最后一个元素，从根结点从上到下过滤元素
    int Parent, Child;
    ElementType Maxitem, temp;
    if (IsEmpty(H))
    {
        printf("最大堆为空\n");
        return ERROR;
    }
    Maxitem = H->Elements[1];
    /* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
    temp = H->Elements[H->Size--];                          /* 注意当前堆的规模要减小 */
    for (Parent = 1; 2 * Parent <= H->Size; Parent = Child) // 2*Parent<=Size是为了确保它有孩子结点，以继续进行比较。
    {
        Child = 2 * Parent;
        if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1])) //找出左右孩子中较大那个
        {
            Child++; /* Child指向左右子结点的较大者 */
        }
        if (temp >= H->Elements[Child]) //不用继续往下比较了，可能到了末尾结点或者该子树的元素都比item要小。
            break;
        else /* 下滤X */
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }
    H->Elements[Parent] = temp;
    return Maxitem;
}
// 04最小堆的删除
ElementType DeleteMin(HeapTree H) //从最小堆H中取出键值最小的元素，并删除该结点
{                                 //方法：用最小堆中的最后一个元素，从根结点从上到下过滤元素
    int Parent, Child;
    ElementType Minitem, temp;
    if (IsEmpty(H))
    {
        printf("最小堆为空\n");
        return ERROR;
    }
    Minitem = H->Elements[1];
    /* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
    temp = H->Elements[H->Size--];                          /* 注意当前堆的规模要减小 */
    for (Parent = 1; 2 * Parent <= H->Size; Parent = Child) // 2*Parent<=Size是为了确保它有孩子结点，以继续进行比较。
    {
        Child = 2 * Parent;
        if ((Child != H->Size) && (H->Elements[Child] > H->Elements[Child + 1])) //找出左右孩子中较小那个
        {
            Child++; /* Child指向左右子结点的较小者 */
        }
        if (temp <= H->Elements[Child]) //不用继续往下比较了，可能到了末尾结点或者该子树的元素都比item要大。
            break;
        else /* 下滤X */
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }
    H->Elements[Parent] = temp;
    return Minitem;
}
//05建立最大堆：建立一个完全二叉树，从最后一个有儿子的父结点开始逐个往前建堆，将每一个子堆都调整为最大堆，调的方法与删除堆顶元素的方法类似
//此方法相较于逐个元素插入的方法，可以降低时间复杂度，NlogN->N
/*----------- 建造最大堆 -----------*/
void PercDownMax(HeapTree H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElementType X;

    X = H->Elements[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))
            Child++; /* Child指向左右子结点的较大者 */
        if (X >= H->Elements[Child])/* 找到了合适位置 */
            break; 
        else       /* 下滤X */
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = X;
}
void BuildHeapMax(HeapTree H)
{ /* 调整H->Elements[]中的元素，使满足最大堆的有序性  */
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
    int i;
    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDownMax(H, i);
}
//05建立最小堆：建立一个完全二叉树，从最后一个有儿子的父结点开始逐个往前建堆，将每一个子堆都调整为最小堆，调的方法与删除堆顶元素的方法类似
//此方法相较于逐个元素插入的方法，可以降低时间复杂度，NlogN->N
/*----------- 建造最小堆 -----------*/
void PercDownMin(HeapTree H, int p)
{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
    int Parent, Child;
    ElementType X;

    X = H->Elements[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size) && (H->Elements[Child] > H->Elements[Child + 1]))
            Child++; /* Child指向左右子结点的较小者 */
        if (X <= H->Elements[Child])/* 找到了合适位置 */
            break; 
        else       /* 下滤X */
            H->Elements[Parent] = H->Elements[Child];
    }
    H->Elements[Parent] = X;
}
void BuildHeapMin(HeapTree H)
{ /* 调整H->Elements[]中的元素，使满足最小堆的有序性  */
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
    int i;
    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->Size / 2; i > 0; i--)
        PercDownMin(H, i);
}
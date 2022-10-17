//多项式加法的实现：采用不带头结点的单项链表，按照指数递减的顺序排列各项
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;              //系数
    int expon;             //指数
    struct PolyNode *link; //指向下一个节点的指针
};
Polynomial P1, P2;
int main(void)
{
    return 0;
}
Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial)malloc(sizeof(struct PolyNode)); //定义了一个临时空节点，作为结果多项式的表头
    front = rear;
    while (P1 && P2) //判断指针是否为空指针，空指针表示多项式结束
    {
        switch (compare(P1->expon, P2->expon))
        {
        case 1: // P1中的数据项指数大
            Attach(P1->coef, P1->expon, &rear);
            P1 = P1->link;
            break;
        case -1: // P2中的数据项指数大
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
            break;
        case 0: //数据项指相同
            sum = P1->coef + P2->coef;
            if (sum) //判断系数和是否为零
                Attach(sum, P1->expon, &rear);
            P1 = P1->link;
            P2 = P2->link;
            break;
        }
    }
    /*将未处理完的另一个多项式的所有节点依次连接到结果多项式中*/
    for (; P1; P1 = P1->link)
        Attach(P1->coef, P1->expon, &rear);
    for (; P2; P2 = P2->link)
        Attach(P2->coef, P2->expon, &rear);
    rear->link = NULL;
    temp = front;
    front = front->link;
    free(temp); //释放空白头节点的空间
    return front;
}
void Attach(int coef, int expon, Polynomial *prear)
{ //这里prear是一个指针变量，传递的是PolyAdd函数中结果多项式尾节点指针变量rear的地址
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); //创建新节点用于存储结果的系数和指数值，函数结束该内存不会被回收。
    P->coef = coef;
    P->expon = expon;
    P->link = NULL;
    (*prear)->link = P;
    *prear = P; //使尾节点指针变量指向新节点
}
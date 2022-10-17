//设计函数分别求两个一元多项式的乘积与和
//已知两个多项式:(1) 3x4 - 5x2 + 6x - 2，(2) 5x20 - 7x4 + 3x；
//多项式和:5x20 - 4x4- 5x2 + 9x - 2
//多项式乘积:15x24-25x22+30x21-10x20-21x8+35x6-33x5+14x4-15x3+18x2-6x

/*设计思路*/
// 1多项式表示：采用链表进行设计，每个节点包含：系数值coef，指数值expon，下一节点指针
// 2程序框架：读入多项式1和2，加法运算并输出，乘法运算并输出
// 3读入多项式：创建新节点，存入信息，并连接到已有节点后，返回头节点指针。这里创建的是不带头节点的线性表。
// 4两个多项式相加：创建结果头节点，依次判断两个多项式指数是否相同。输入和输出均为不带头结点的线性表，
//   若相同则相加结果不为零时创建节点连接到已有多项式后，若不同将高次项连接到结果多项式，继续比较，
//   当有一多项式链表指向空时停止比较，将零一多项式剩余部分连接到结果多项式后，并返回结果多项式链表的头节点指针。
// 5两个多项式的乘法1：将P1的每一项与P2相乘，并加入结果多项式中；
//   对于P1一项与P2相乘的每一步，要先申请空间存入相乘结果，并将结果与输出结果P相加，再释放掉P2的空间。
// 6两个多项式的乘法2：逐项插入，将P1第i项与P2第j项相乘，并插入到结果多项式。对于初始结果多项式，可由P1第1项与P2相乘得到。
//  插入时，需要考虑结果多项式是否为空；若不为空，需要判断插入位置，末尾，中间或前面，注意释放空间；
//  若插入中间，需要判断是否存在指数相等的项；若存在指数相等的项，需要判断是否会导致该项系数为零

#include <stdio.h>
#include <stdlib.h>
typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;              //系数
    int expon;             //指数
    struct PolyNode *link; //指向下一个节点的指针
};

Polynomial PolyRead();                                   //读入多项式
Polynomial Mult1(Polynomial P1, Polynomial P2);          //乘法1实现
Polynomial Mult2(Polynomial P1, Polynomial P2);          //乘法2实现
Polynomial PolyAdd(Polynomial P1, Polynomial P2);        //加法实现
void PrintPoly(Polynomial P);                            //显示多项式
void Attach(int coef, int expon, Polynomial *prear);     //连接
int compare(int e1, int e2);                             //比较
Polynomial CopyPoly(Polynomial P1);                      //复制多项式
void InsertNode(int coef, int expon, Polynomial *prear); //将结果项插入到结果多项式合适位置
int main(void)
{
    Polynomial P1, P2, PP1, PP2, PS;
    P1 = PolyRead();
    P2 = PolyRead();
    printf("乘法1>>>\n");
    PP1 = Mult1(P1, P2); //按照方法1相乘的结果
    printf("乘法2>>>\n");
    PP2 = Mult2(P1, P2); //按照方法2相乘的结果
    printf("运算结果>>>\n");
    printf("乘法一运算结果：");
    PrintPoly(PP1);
    printf("乘法二运算结果：");
    PrintPoly(PP2);
    PS = PolyAdd(P1, P2);
    printf("加法运算结果：");
    PrintPoly(PS);
    while (1);
    return 0;
}
Polynomial PolyRead()
{
    int N, c, e;
    Polynomial rear, temp, P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    rear = P;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &rear);
        // temp = (Polynomial)malloc(sizeof(struct PolyNode));
        // temp->expon = e;
        // temp->coef = c;
        // temp->link = NULL;
        // PP->link = temp;
        // PP = temp;
    }
    temp = P;
    P = P->link;
    free(temp);
    //这里最好输出一下，进行一下检查
    printf("输入多项式：");
    PrintPoly(P);
    return P;
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
    //函数功能：将新节点添加到（*prear）节点后
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); //创建新节点用于存储结果的系数和指数值，函数结束该内存不会被回收。
    P->coef = coef;
    P->expon = expon;
    P->link = NULL;
    (*prear)->link = P;
    *prear = P; //使尾节点指针变量指向新节点
}
int compare(int e1, int e2)
{
    if (e1 == e2)
        return 0;
    if (e1 > e2)
        return 1;
    if (e1 < e2)
        return -1;
}
Polynomial Mult1(Polynomial P1, Polynomial P2)
{
    Polynomial P, prear, P0, t1, t2;
    t1 = P1;

    int i = 1;
    P0 = (Polynomial)malloc(sizeof(struct PolyNode)); //创建一个空节点，存放P1第i项与P2相乘的结果
    P0->link = NULL;
    while (P1)
    {
        t2 = P2;
        P0 = (Polynomial)malloc(sizeof(struct PolyNode)); //创建一个空节点，存放P1第i项与P2相乘的结果
        P0->link = NULL;
        prear = P0; //存放计算的临时结果，每次计算产生的临时结果链表空间一定是一样长的。
        while (t2)
        {
            Attach(P1->coef * t2->coef, P1->expon + t2->expon, &prear); //多项式系数一定不为0
            t2 = t2->link;
        }
        printf("P1_%d * P2=",i);
        PrintPoly(P0->link);
        if (i == 1) //第一次运算，直接将临时结果P0的值赋给P
        {
            P = CopyPoly(P0->link);
        }
        else //不是第一次运算，可以使用多项式相加函数，注意临时结果P0的头节点为空
        {
            P = PolyAdd(P, P0->link);
        }
        P1 = P1->link;
        i++;
        while (P0) //释放掉临时结果的链表空间，每次计算产生的临时结果链表空间一定是一样长的。
        {
            Polynomial temp;
            temp = P0;
            P0 = P0->link;
            free(temp);
        }
    }
    return P;
}
Polynomial Mult2(Polynomial P1, Polynomial P2)
{
    Polynomial t1, t2, P, prear, temp;
    int coef, expon, i, j;
    t1 = P1;
    t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); //创建一个空节点，存放计算结果。
    P->link = NULL;
    prear = P; //表示P的尾节点
    while (t2)
    {
        Attach(P1->coef * t2->coef, P1->expon + t2->expon, &prear); //多项式系数一定不为0
        t2 = t2->link;
    }
    t1 = t1->link;
    printf("P1_1 * P2=");
    PrintPoly(P->link);
    i = 2;
    while (t1)
    {
        t2 = P2;
        j = 1;
        while (t2)
        {
            coef = t1->coef * t2->coef;
            expon = t1->expon + t2->expon;
            InsertNode(coef, expon, &P); //将结果项插入到结果多项式中
            t2 = t2->link;
            printf("P1_%d * P2_%d=%dX^%d,结果多项式：", i, j, coef, expon);
            PrintPoly(P->link);
            j++;
        }
        i++;
        t1 = t1->link;
    }
    temp = P;
    P = P->link;
    free(temp);
    return P;
}
void PrintPoly(Polynomial P)
{
    if (!P)
    {
        printf("0 0");
        return;
    }
    while (P)
    {
        printf(" %dX^%d ", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
    return;
}
Polynomial CopyPoly(Polynomial P0)
{
    Polynomial P, temp;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    temp = P;
    while (P0)
    {
        Attach(P0->coef, P0->expon, &temp);
        P0 = P0->link;
    }
    temp = P;
    P = P->link;
    free(temp);
    return P;
}
void InsertNode(int coef, int expon, Polynomial *prear)
{ //将结果项插入到结果多项式合适位置
    Polynomial temp1, temp2, NewNode;
    int sum;
    temp1 = (*prear)->link;
    if (!temp1) //结果多项式为空
    {
        printf("临时结果多项式为空,插入前：");
        PrintPoly(temp1);
        temp1 = NewNode;
        temp1->coef = coef;
        temp1->expon = expon;
        temp1->link = NULL;
        printf("插入后：");
        PrintPoly(temp1);
    }
    else //结果多项式不为空
    {
        NewNode = (Polynomial)malloc(sizeof(struct PolyNode));
        NewNode->coef = coef;
        NewNode->expon = expon;
        while (temp1 && temp1->expon > expon) //若结果多项式非空，筛选出temp2>NewNode>=temp1
        {
            temp2 = temp1;
            temp1 = temp1->link;
        }
        if (temp1 == NULL) //情况1：插入在结果末尾
        {
            temp2->link = NewNode;
            NewNode->link = NULL;
        }
        else if (temp1->expon == expon) //情况2：存在一项temp1，指数相同
        {
            sum = temp1->coef + coef;
            if (sum) //指数相同，且和不为零
            {
                temp1->coef = sum;
                free(NewNode);
            }
            else //指数相同，且和为零
            {
                temp2->link = temp1->link;
                free(temp1);
                free(NewNode);
            }
        }
        else //情况3：指数在temp2和temp1之间
        {
            temp2->link = NewNode;
            NewNode->link = temp1;
        }
    }
}
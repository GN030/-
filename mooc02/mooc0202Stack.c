//线性表的链式存储实现
//01.存储实现
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct LNode *List;
struct LNode
{
    ElementType Data;
    List Next;
};

int main(void)
{
    struct LNode L;
    List PtrL;
}
//02.求表长
int Length(List PtrL)
{
    List p=PtrL;//相当于struct LNode *p = PtrL,表示初始化一个结构体LNode指针变量，同时将指针变量PtrL的值赋给p;
/*指针初始化：int *a=&x;
赋值：a="abc";a=&x;
使用：*a=5*/
    int j=0;
    while(p)//while(指针)，判断是不是空指针，相当于NULL！=p，如果是空指针，退出循环；while(*str),如果指针所指向的变量是结束符'\0',退出循环。
    {
        j++;
        p=p->Next;
    }
    return j;
}
//3.按照序号查找
List FindKth(int K,List PtrL)
{
    List p=PtrL;
    int i=1;
    while(p!=NULL&&i<K)
    {
        p=p->Next;
        i++;
    }
    if(i==K)
        return p;
    else return NULL; 
}
//4.按值查找
List Find(ElementType K,List PtrL)
{
    List p=PtrL;
    while(p->Next!=NULL&&p->Data!=K)
        p=p->Next;
    return p;
}
//5.插入(第i-1个节点后插入一个新节点)
List Insert(ElementType X,int i,List PtrL)
{
    List p,s;
    if(i==1)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = PtrL;
        return s;
    }
    p = FindKth(i-1,PtrL);
    if(p==NULL)
    {
        printf('参数错误');
        return NULL;
    }
    else{
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }
}
//6.删除第i个节点
List Delete(int i,List PtrL)
{
    List s,p;
    if(i==1)
    {
        s = PtrL;
        if(PtrL!=NULL)PtrL=PtrL->Next;
        else return NULL;
        free(s);
        return PtrL;
    }
    p = FindKth(i-1,PtrL);
    if(p==NULL)
    {
        printf('第%d个节点不存在',i-1);
        return NULL;
    }
    else if(p->Next==NULL)
    {
        printf('第%d个节点不存在',i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}

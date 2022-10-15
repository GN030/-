//线性表的链式存储实现
//01.存储实现
#include <stdio.h>
#define ElementType int

int main(void)
{
    typedef struct LNode *List;
    struct LNode{
        ElementType Data;
        List Next;
    };
    struct LNode L;
    List PtrL;
}
//常规做法：建立一个足够大的链表数组，0-MaxSize，每次逆转k个结点：
//逆转方法：new，old和temp，每次将后一个结点指向前一个结点，并每k次，将新反转的片段接在新链表后面，将
#include <stdio.h>
#include <stdlib.h>
#define NULL -1
#define MaxSize 100000
Ptr Reverse( Ptr head, int K )
{ cnt = 1;
new = head->next;
old = new->next;
while ( cnt < K ) {
tmp = old->next;
old->next = new;
new = old; old = tmp;
cnt++;
}
head->next->next = old;
return new;
}
#include <stdio.h>
#include <stdlib.h>

void PrintN(int N);

int main()
{
    printf("Hello World!\n");
    printf("你好世界！\n");

    PrintN(100);

    system("pause");
    return 0;
}

void PrintN(int N)
{
    int i;
    for (i=1;i<=N;i++)
    {
        printf("%d\n",i);
    }
    return;
}
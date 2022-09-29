// 实现函数PrintN，打印1-N全部正整数。
// 当N过大时，递归实现函数会报错。

#include <stdio.h>
#include <stdlib.h>

void PrintN(int N);

int main()
{
    printf("Hello World!\n");
    printf("你好世界！\n");

    PrintN(100000);

    system("pause");
    return 0;
}

// void PrintN(int N)
// {
//     int i;
//     for (i=1;i<=N;i++)
//     {
//         printf("%d\n",i);
//     }
//     return;
// }

void PrintN(int N)
{
    if(N){
        PrintN(N-1);
        printf("%d\n",N);
    }
}
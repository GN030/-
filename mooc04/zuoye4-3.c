/*题意：给定一个整数序列，建立成为一个完全二叉搜索树CBST，并按照层序遍历的方法进行打印*/
/*思路：1.因为是完全二叉树形式，并且进行层序遍历，可以采用数组存储*/
/*2.将输入序列按照大小顺序排序，在CBST中，左子树结点值一定都小于根结点值，右子树结点值一定都大于根结点值*/
/*3.找到根结点的位置：根据元素个数n，计算层数和左子树节点个数，从而确定根结点位置，利用递归的方法得到完整的CBST*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ElementType int
#define MaxSize 10000
int A[MaxSize]; /*保存输入的数据*/
int T[MaxSize]; /*保存完全二叉搜索树数据*/

int compare(const void *a, const void *b);    /*对数字排序需要用到的程序*/
void solve(int ALeft, int ARight, int TRoot); /*输入树左右边界序号，及根结点序号，找出根结点元素，并递归*/
int GetLeftLength(int n);                     /*计算完全二叉树（结点数n）的左子树结点数目*/
int main(void)
{
    int N, i, TRoot;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &A[i]);
    qsort(A, N, sizeof(int), compare);
    solve(0, N - 1, 0);
    /*打印层序遍历结果*/
    for (i = 0; i < N - 1; i++)
    {
        printf("%d ", T[i]);
    }
    printf("%d", T[i]);
    return 0;
}
int compare(const void *a, const void *b)
{ /*对数字排序需要用到的程序*/
    return *(int *)a - *(int *)b;
}
void solve(int ALeft, int ARight, int TRoot)
{ /*输入树左右边界序号，及根结点序号，找出根结点元素，并递归；初始调用为 solve(0, N-1, 0) */

    int n, L, LeftTRoot, RightTRoot;
    n = ARight - ALeft + 1; /*当前序列长度*/
    if (n == 0)
        return;
    L = GetLeftLength(n); /*计算完全二叉树（结点数n）的左子树结点数目*/
    T[TRoot] = A[ALeft + L];
    LeftTRoot = 2 * TRoot + 1;
    RightTRoot = LeftTRoot + 1;
    solve(ALeft, ALeft + L - 1, LeftTRoot);
    solve(ALeft + L + 1, ARight, RightTRoot);
}
int GetLeftLength(int n)
{ /*计算完全二叉树（结点数n）的左子树结点数目*/
    int i, count = 0;
    for (i = 0; count < n;)
    {
        i++;
        count = count + pow(2, i - 1);
    }
    if (count == n)               /*树高为i,满二叉树*/
        return pow(2, i - 1) - 1; /*左子树结点个数2^(i-1)-1*/
    else if (count > n)           /*树高为i，完全二叉树*/
    {
        int item;                                      /*最后一层属于左子树的结点数*/
        if ((n - (pow(2, i - 1) - 1)) > pow(2, i - 2)) /*最后一层结点多于一半*/
            item = pow(2, i - 2);
        else
            item = n - (pow(2, i - 1) - 1);
        return item + pow(2, i - 2) - 1; /*左满二叉子树层数为i-2*/
    }
}
/*input test*/
// 10
// 1 2 3 4 5 6 7 8 9 0
/*output*/
// 6 3 8 1 5 7 9 0 2 4
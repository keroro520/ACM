/*
    构造题

    题意 : 给一个n, 求出3个0 ~ n-1的全排列{a}, {b}, {c}, 使得
           (ai + bi) % n == ci % n


    第一次打cf. 这是赛后在"neko小队"里一个人的解法.
    {a} = 0,1,2,3,4...,n-1
    a移动一下位置就可以得出b了...下面的代码是移动一位, 其实移动多少位都可以. 即ai == b(i+move).
*/
#include <stdio.h>
#define N   100001
int a[N], b[N];

int main()
{
    int n;
    scanf("%d", &n);
    if((n & 1) == 0) {
        printf("-1\n");
        return 0;
    }
    for(int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = (i-1 + n) % n;
    }
    for(int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
    for(int i = 0; i < n; i++) printf("%d ", b[i]);
    printf("\n");
    for(int i = 0; i < n; i++) printf("%d ", (a[i] + b[i]) % n);
    printf("\n");
    return 0;
}

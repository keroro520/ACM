/*
    序列题  思路题

    题意：序列初始为{0}，3种操作：(1)把x加到前i个元素上 (2)把k添加到序列末尾 (3)把序列的最后一个元素删掉
          要求在每一次操作完后输出序列的平均值


    思路：“线性线段树”的做法。
          add[i]记录a[1]..a[i]要加的数。每做依次操作3，就a[n-1] += a[n], n--;
          总和和个数很容易维护.
          刚开始还想用线段树，大材小用了。
*/
#include <stdio.h>
#define     MAXN    200005

int rec[MAXN], a[MAXN];
int main()
{
    int cases, op, x, i;
    double sum = 0;
    int    n   = 1;
    a[0] = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            rec[i-1] += x;
            sum += i * x;
        } else if(op == 2) {
            scanf("%d", &x);
            a[n]   = x;
            rec[n] = 0;
            n++;
            sum += x;
        } else {
            rec[n-2] += rec[n-1];
            sum -= a[n-1] + rec[n-1];
            n--;
        }
        printf("%.6f\n", sum/n);
    }
    return 0;
}

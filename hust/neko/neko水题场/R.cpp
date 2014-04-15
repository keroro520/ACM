/*
    题意：序列1, 12, 123, 1234, ... , 123456789, 12345678910...，给你A,B,算出该序列中第A个数到第B个数里面有多少个能被3整除。

    思路：规律很好找，序列里面的数是否能被3整除的序列为:N, Y, Y, N, Y, Y, N... 
*/
//lightoj 1136
//http://acm.hust.edu.cn/vjudge/contest/view.action?cid=28015#problem/R
#include <stdio.h>

int calc(int x)
{
    return x/3*2 + (x % 3 != 0) * (x % 3 - 1);
}
int main()
{
    int cases, Cas = 0, A, B;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &A, &B);
        printf("Case %d: %d\n", ++Cas, calc(B) - calc(A-1));
    }
    return 0;
}

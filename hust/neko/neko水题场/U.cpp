/*
    题意：在一个无限大的棋盘上，放有两只象，象每一步可以沿着对角线走不限的格子。问两只象最少要多少步数才能相遇。

    思路：一开始读错题意，以为一步只能走一格，这时解为 Max(横座标的差值，纵座标的差值)

          正确题意的解为: 先由奇偶性判断是否impossible；是否在一条斜线上，答案为1；否则为2


    竟然WA了3次.... 感觉不会再爱了...
*/
//lightoj 1202
// http://acm.hust.edu.cn/vjudge/contest/view.action?cid=28015#problem/U

#include <stdio.h>
#include <math.h>
#define         ZERO        0.000000001

int main()
{
    int cases, Cas = 0;
    int x1,x2,y1,y2;
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d: ", ++Cas);
        scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
        if(((x1+y1) & 1) != ((x2+y2) & 1)) {printf("impossible\n"); continue;}
        int k = x2 - x1;
        if(y1 + k == y2 || y1 - k == y2) printf("1\n");
        else printf("2\n");
    }
    return 0;
}

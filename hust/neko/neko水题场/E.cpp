/*
    题意：棋盘放马   n*m棋盘，马的攻击方式跟象棋一样。问最多能放多少马？

    思路：neko一句“黑马只攻击白格”提醒了我，结果不就是(n*m+1)/2吗。
          但是这个公式遇到小数据则会跪。目前只知道m = 1和m = 2的特例，m = 1时答案为n；m = 2时可以把棋盘分割成2*4的若干小块，每一2*4小块能放4个马，剩余不足2*4的块特搞一下即可。
*/
//Light OJ 1010
#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    int cases, n, m, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        printf("Case %d: ", ++Cas);
        if(m > n) swap(n, m);
        if(m == 1) printf("%d\n", n);
        else if(m == 2) printf("%d\n", n/4*4 + (n % 4 != 0) * 2 * (n%4/2+1));
        else printf("%d\n", (n*m+1)/2);
    }
    return 0;
}

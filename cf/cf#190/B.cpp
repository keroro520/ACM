/*
    思路题   好题

    题意：r朵红花，b朵蓝花，g朵绿花，一束花可以是3朵单色花，或者3种颜色的花各一朵混合，问最多可以组成多少束？

    思路：先尽量混合组，再用剩余的花单色组。
          但有一点特别重要，比如剩下两朵红花两朵蓝花，这时最优答案应该是把一组混合束拆开，和这两朵红花两朵蓝花组成两束单色束。这一点是 伲鑫发现的，我觉得我很难会想到这一点。
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
    int r,g,b;
    scanf("%d%d%d", &r, &g, &b);
    int mm = min(min(r, g), b);
    int ans = mm;
    ans += (r-mm) / 3 + (g-mm) / 3 + (b-mm) / 3;
    r = (r-mm) % 3, g = (g-mm) % 3, b = (b-mm) % 3;
    if(mm != 0 && r + g + b == 4) ans++;        //忘了mm ==  0的情况，直接system judge WA
    printf("%d\n", ans);
    return 0;
}

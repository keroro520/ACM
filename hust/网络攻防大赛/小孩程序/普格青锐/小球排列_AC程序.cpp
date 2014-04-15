#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    freopen("ball_in.txt","r", stdin);
     freopen("ball_ans.txt","w", stdout);
    int cases, ans, ta, tb, tc, a, b, c;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &ta, &tb, &tc);
        a = min(ta, min(tb, tc)), c = max(ta, max(tb, tc)), b = (ta + tb + tc) - (a + c);
        if(c - a >= 2) ans = 0;
        else if(a == b && b == c) ans = 6;
        else if(a != b && b == c) ans = 2;
        else if(a == b && b != c && a == 0) ans = 1;
        else if(a == b && b != c && a != 0) ans = 2;


        printf("%d\n", ans);
    }
    return 0;
}

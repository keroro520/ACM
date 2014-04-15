#include <stdio.h>
#include <algorithm>
using namespace std;
int main()
{
    int cases, x, n;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        int ans = 0, sum = 0, maxx = -999999999;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            maxx = max(x, maxx);
            sum += x;
            if(sum < x) sum = x;
            if(sum < 0) {
                sum = 0;
            } else if(sum > ans) ans = sum;
        }
        if(ans == 0) {
            ans = maxx;
        }
        printf("%d\n", ans);
    }
    return 0;
}

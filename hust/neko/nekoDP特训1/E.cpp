/*
    跑数据才知道是方程转移的时候初始化错了。
    f[i][j] = f[i-1][j] ，为什么写成f[i][j] = f[i-1][j-1] + 1会错呢？ 因为逻辑就不对！  逻辑不对！！f[i,j]当然是要初始化为前面子状态的最优值f[i-1,j]呀！f[i-1][j-1]是转移方程时候的子状态。
    所以要注意注意，要是没有数据的话那我不是一直WA了 =_=
*/
//lightoj 1017
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN        105

int a[MAXN], n, f[MAXN][MAXN];

int main()
{
    int cases, Cas = 0, W, K;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &n, &W, &K);
        for(int i = 1; i <= n; i++) scanf("%*d%d", &a[i]);
        sort(a+1, a+n+1);
        memset(f, 128, sizeof(f));
        for(int i = 0; i <= n; i++) f[i][0] = 0;
        for(int i = 0; i <= K; i++) f[0][i] = 0;
        f[0][0] = 0;
        int ans = 0;
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= K; j++) {
                f[i][j] = f[i-1][j];        //f[i-1][j-1] + 1           //TODO
                for(int k = i; k > 0 && a[i]-a[k] <= W; k--)
                    f[i][j] = max(f[i][j], f[k-1][j-1] + i - k + 1), ans = max(ans, f[i][j]);
                //printf("# %d  %d   %d\n", i,j,f[i][j]);
            }
        printf("Case %d: %d\n", ++Cas, ans);
    }
    return 0;
}

/*
    记忆化搜索  DP  好题

    又是道DP被雷给搜过的题。。。好崇拜好自卑。。。为什么人家能记忆化搞过我就想不到呢。。。

    题意：n个人，每个人站在x轴上某一点。每个人最多走K的长度。现在这些人要走成若干堆，每堆至少3个人。问最少可以走成多少堆？
*/
//lightoj 1084
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     MAXN    100005
#define     INF     999999999
int a[MAXN], n, Limit, f[MAXN];
int dfs(int idx)
{
    if(idx == n) return 0;
    if(f[idx] != -1) return f[idx];
    int nxt = upper_bound(a, a+n, a[idx]+Limit) - a;

    int &ans = f[idx];
    ans = INF;
    if(nxt - idx >= 3) ans = min(ans, dfs(nxt) + 1);        //感觉很棒呀。。。。。。。。。。。我怎么就是不会记忆化搜呢。。。。。。
    if(nxt - idx >= 4) ans = min(ans, dfs(nxt-1) + 1);
    if(nxt - idx >= 5) ans = min(ans, dfs(nxt-2) + 1);
    return ans; 
}

int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &Limit);
        Limit *= 2;
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a+n);
        memset(f, -1, sizeof(f));
        int ans = dfs(0);
        printf("Case %d: %d\n", ++Cas, ans == INF ? -1 : ans);
    }
    return 0;
}

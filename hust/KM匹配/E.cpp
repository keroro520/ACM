/*
    KM  二分图带权匹配  简单题

    题意：N个箱子围成一圈，每个箱子里可能头0颗或者若干颗巧克力，总数目不超过N。现要求移动这些巧克力使得每个箱子有不超过1个巧克力，求最少步数。移动一步可以把箱子里的一个巧克力放置到相邻的箱子里面。

    思路：对有超过1个巧克力的箱子拆成a[i]-1个点作为X部，对有0个巧克力的箱子作为Y部，KM匹配。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define         ABS(x)      ((x) > 0 ? (x) : (-(x)))
#define         MAXN        505
int LX[MAXN], LY[MAXN], slack[MAXN], link[MAXN], visx[MAXN], visy[MAXN];
int edge[MAXN][MAXN], id[2][MAXN];
int when = 1, n, m, N;
int dis(int x, int y)
{
    return min(ABS(x-y), N - (ABS(x-y)));
}
bool find(int u)
{
    visx[u] = when;
    for(int v = 0; v < m; v++) if(visy[v] != when) {
        int rest = LX[u] + LY[v] - edge[u][v];
        if(rest == 0) {
            visy[v] = when;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack[v] = min(slack[v], rest);
    }
    return false;
}
void KM()
{
    memset(LX, 128, sizeof(LX));
    memset(LY,   0, sizeof(LY));
    memset(link,-1, sizeof(link));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) LX[i] = max(LX[i], edge[i][j]);
    for(int start = 0; start < n; start ++) {
        for(int i = 0; i < m; i++) slack[i] = (INT_MAX);
        while(true) {
            when++;
            if(find(start)) break;
            else {
                int d = (INT_MAX);
                for(int i = 0; i < m; i++) if(visy[i] != when) d = min(d, slack[i]);
                for(int i = 0; i < n; i++) if(visx[i] == when) LX[i] -= d;
                for(int i = 0; i < m; i++)
                    if(visy[i] == when) LY[i] += d;
                    else slack[i] -= d;
            }
        }
    }
}
int main()
{
    int x;
    while(scanf("%d", &N) != EOF) {
        n = m = 0;
        for(int i = 0; i < N; i++) {
            scanf("%d", &x);
            if(x == 0) id[0][m++] = i;
            if(x >  1) {
                while(x > 1) {
                    x--;
                    id[1][n++] = i;
                }
            }
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                edge[i][j] = -dis(id[1][i], id[0][j]);
            }
        KM();
        int ans = 0;
        for(int i = 0; i < m; i++) if(link[i] != -1) ans += LX[link[i]] + LY[i];
        printf("%d\n", -ans);
    }
    return 0;
}

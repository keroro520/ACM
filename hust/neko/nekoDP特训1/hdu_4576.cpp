/*
    简单概率DP

    递归TLE
    递推AC
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    205
int n;
double f[2][MAXN];

int main()
{
    int query, L, R, w;
    while(scanf("%d%d%d%d", &n, &query, &L, &R), n+query+L+R) {
        L--, R--;
        int cur = 0;
        memset(f, 0, sizeof(f));
        f[cur][0] = 1.0;
        while(query--) {
            scanf("%d", &w);
            cur ^= 1;
            for(int i = 0; i < n; i++) {
                f[cur][i] = (f[cur^1][(i+w+n) % n] + f[cur^1][(i-w+n) % n]) * 0.5;
            }
        }
        double ans = 0;
        while(L <= R) ans += f[cur][L], L++;
        printf("%.4f\n", ans);
    }
    return 0;
}

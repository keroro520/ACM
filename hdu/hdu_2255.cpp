/*
    KM   二分图带权匹配模板题
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define     MAXN    305
int n, slack;
int LX[MAXN], LY[MAXN], a[MAXN][MAXN], link[MAXN];
bool visx[MAXN], visy[MAXN];

bool find(int u)
{
    visx[u] = true;
    for(int v = 0; v < n; v++) if(!visy[v]) {
        int rest = LX[u] + LY[v] - a[u][v];
        if(rest == 0) {
            visy[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack = min(slack, rest);
    }
    return false;
}
void KM()
{
    memset(link, -1, sizeof(link));
    memset(LY,    0, sizeof(LY));
    memset(LX,  128, sizeof(LX));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            LX[i] = max(LX[i], a[i][j]);
    for(int i = 0; i < n; i++) {
        while(true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            slack = (INT_MAX);
            if(find(i)) break;
            for(int i = 0; i < n; i++) if(visx[i]) LX[i] -= slack;
            for(int i = 0; i < n; i++) if(visy[i]) LY[i] += slack;
        }
    }
}
int main()
{
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &a[i][j]);
        KM();
        int ans = 0;
        for(int i = 0; i < n; i++) ans += a[link[i]][i];
        printf("%d\n", ans);
    }
    return 0;
}

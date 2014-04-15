/*
    最大流模板题   EK模板   Ford_Forkson模板
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <deque>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    205
#define     INF     999999999
int c[MAXN][MAXN], f[MAXN][MAXN], pre[MAXN];
bool visit[MAXN];
int n;
void init()
{
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));
}
bool Ford_Forkson(int s, int t)
{
    memset(visit, false, sizeof(visit));
    visit[s] = true;
    deque<int> Q;
    Q.push_back(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        for(int v = 1; v <= n; v++) if(!visit[v] && c[u][v] > f[u][v]) {
            Q.push_back(v);
            visit[v] = true;
            pre[v] = u;
            if(v == t) return true;
        }
    }
    return false;
}
int EK(int s, int t)
{
    int ans = 0;
    while(Ford_Forkson(s, t)) {
        int v = t, mm = INF;
        do {
            mm = min(mm, c[pre[v]][v] - f[pre[v]][v]);
            v = pre[v];
        } while(v != s);
        v = t;
        do {
            f[pre[v]][v] += mm;
            f[v][pre[v]] -= mm;
            v = pre[v];
        } while(v != s);
        ans += mm;
    }
    return ans;
}

int main()
{
    int m, x, y, z;
    while( scanf("%d%d", &m, &n) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            c[x][y] += z;
        }
        printf("%d\n", EK(1, n));
    }
    return 0;
}

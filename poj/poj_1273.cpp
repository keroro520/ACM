/*
    最大流 模板题

    EK算法

    时隔1年半，虽说是看了模板后敲的，不过1A了还是有点小讶异
*/
#include <stdio.h>
#include <deque>
#include <string.h>
using namespace std;
#define     INF     99999999
#define     MAXN    205
#define     debug   printf("!\n")
int n;
int pre[MAXN], c[MAXN][MAXN], f[MAXN][MAXN];
bool visit[MAXN];

bool solve(int s, int t)
{
    deque<int> Q;
    memset(visit, false, sizeof(visit));
    visit[s] = true;
    Q.push_back(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        if(u == t) return true;
        for(int v = 1; v <= n; v++) if(!visit[v] && c[u][v] > f[u][v]) {
            visit[v] = true;
            pre[v] = u;
            Q.push_back(v);
        }
    }
    return false;
}

int  max_flow(int s, int t)
{
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++) f[i][j] = f[j][i] = 0;

    int ans = 0;
    while(solve(s,t)) {
        int Min = INF, v = t;
        do {
            Min = min(Min, c[pre[v]][v] - f[pre[v]][v]);
            v = pre[v];
        } while(v != s);
        v = t;
        ans += Min;
        do {
            f[pre[v]][v] += Min;
            f[v][pre[v]] -= Min;    //跟直接取f[pre[v]][v]反有不同吗
            v = pre[v];
        } while(v != s);
    }
    return ans;
}

int main()
{
    int m, x, y, z;
    while(scanf("%d%d", &m, &n) != EOF) {
        memset(c, 0, sizeof(c));
        while(m--) {
            scanf("%d%d%d", &x, &y, &z);
            c[x][y] += z;
        }
        printf("%d\n", max_flow(1, n));
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#define     MAXN    50005
#define     MAXK    505
#define     MOD     10007

int n, K, edge_num;
int head[MAXN], deg[MAXN], dis[MAXN], visit[MAXN], Value[MAXN][MAXK], ans[MAXN];
struct Edge {
    int v, next; 
} edge[MAXN * 4];

void add_edge(int u, int v)
{
    edge[edge_num].next = head[u];
    edge[edge_num].v = v;
    head[u] = edge_num++;
}

void prework()
{
    for(int k = 0; k <= 500; k++) Value[0][k] = 0;
    for(int i = 1; i <= 5000; i++) Value[i][0] = 1;
    for(int i = 1; i <= 50000; i++)
        for(int k = 1; k <= 500; k++)
            Value[i][k] = Value[i][k-1] * i % MOD;
}
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));
    memset(dis, 0, sizeof(dis));
    memset(visit, 0, sizeof(visit));        //int[]
}
void calc(int u, int len)
{
    visit[u] = 1;
    dis[u]   = len;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visit[v] == 1) continue;
        calc(v, len+1);
    }
}
void dfs(int u)
{
    visit[u] = 2;
    ans[u] = 0;
    for(int j = 1; j <= n; j++) ans[u] = (ans[u] + Value[dis[j]][K]) % MOD;
    for(int i = 1; i <= n; i++) 
        if(visit[i] == 1) dis[i]--;
        else dis[i]++;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visit[v] == 2) continue;
        dfs(v);
    }
    for(int i = 1; i <= n; i++) 
        if(visit[i] == 1) dis[i]++;
        else dis[i]--;
    visit[u] = 1;
}
int main()
{
    int cases, x, y;
    prework();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &K);
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
            deg[x]++, deg[y]++;
        }
        for(int i = 1; i <= n; i++) if(deg[i] == 1) {
            calc(i, 0);
            dfs(i);
            break;
        }
        for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    }
    return 0;
}

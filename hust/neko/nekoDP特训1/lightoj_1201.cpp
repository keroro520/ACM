/*
    经典树形DP  

    好像又叫“xx守卫”什么的，挺简单的，略了

*/
//lightoj 1201
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define         MAXN            1005
int f[MAXN][2], head[MAXN];
struct Edge {
    int v, next;
} edge[MAXN * MAXN];
int n, m, edge_num;

void DP(int u, int father)
{
    int sum1 = 0, sum2 = 0;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(v == father) continue;
        DP(v, u);
        sum1 += f[v][0];
        sum2 += max(f[v][0], f[v][1]);
    }
    f[u][0] = sum2 ;
    f[u][1] = sum1 + 1;
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void init()
{
    memset(head, -1, sizeof(head));
    edge_num = 0;
}
int main()
{
    int cases, Cas = 0, u, v;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        init();
        while(m--) {
            scanf("%d%d", &u, &v);
            add_edge(u, v), add_edge(v, u);
        }
        int ans = 0;
        memset(f, -1, sizeof(f));
        for(int i = 1; i <= n; i++) if(f[i][0] == -1) {
            DP(i, 0);
            ans += max(f[i][0], f[i][1]);
        }
        printf("Case %d: %d\n", ++Cas, ans);
    }
    return 0;
}

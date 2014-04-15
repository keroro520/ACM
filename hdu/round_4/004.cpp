#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN        100005
#define     MAXM        100005
struct Edge {
    int v, next;
} edge[MAXM];
long long num[MAXN];
int dfn[MAXN], low[MAXN], S[MAXN * 2], head[MAXN], belong[MAXN], in_deg[MAXN], out_deg[MAXN];
bool in_stack[MAXN];
int edge_num, Index, Order, n, S_top;
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
    in_stack[u] = true;
    S[S_top++] = u;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        int x;
        do {
            num[Order]++;
            x = S[--S_top];
            belong[x] = Order;
            in_stack[x] = false;
        } while(x != u);
        Order++;
    }
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void init()
{
    edge_num = 0;
    Index = 1;
    Order = 0;
    memset(in_stack, false, sizeof(in_stack));
    memset(num, 0, sizeof(num));
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(in_deg, 0, sizeof(in_deg));
    memset(out_deg, 0, sizeof(out_deg));
}

int main()
{
    int cases, Cas = 0, m, x ,y;
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d: ", ++Cas);
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
        }
        for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
        if(Order == 1) {
            printf("-1\n");
            continue;
        }
        for(int i = 1; i <= n; i++)
            for(int k = head[i]; k != -1; k = edge[k].next) {
                int v = edge[k].v;
                if(belong[v] == belong[i]) continue;
                in_deg[belong[v]]++, out_deg[belong[i]]++;
            }
        int MM = 99999999;
        for(int i = 0; i < Order; i++) if((in_deg[i] == 0 || out_deg[i] == 0) &&MM > num[i]) MM = num[i];

        long long ans = (long long)(n - MM) * (long long) (n - 1);
        ans += (MM * (MM - 1));
        printf("%I64d\n", ans - m);
    }
    return 0;
}

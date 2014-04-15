/*
    双连通   边双连通   桥的求解

    题意：给出一个连通图，输出桥的编号。

    思路：桥(u,v)的充要条件：dfn[u] < low[v]
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    10005
#define     MAXM    1000005*2
int n, edge_num, Index, ans;
int dfn[MAXN], low[MAXN], head[MAXN];
bool visit[MAXM];
struct Edge { int v, w, next; } edge[MAXM];

void init()
{
    Index = 1;
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(dfn,  0 , sizeof(dfn));
    memset(visit, false, sizeof(visit));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
    head[u] = edge_num++;
}
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
    for(int k = head[u]; k != -1; k = edge[k].next) if(!visit[k]) {
        visit[k] = visit[k^1] = true;
        int v   = edge[k].v;
        if(!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) ans = min(ans, edge[k].w);
        } else low[u] = min(low[u], dfn[v]);
    }
}
int main()
{
    int m, x, y, z;
    while(scanf("%d%d", &n, &m)!= EOF && n && m) {
        init();
        for(int i = 1; i <= m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, z);
            add_edge(y, x, z);
        }
		ans = 999999999;
        Tarjan(1);
		bool flag = true;
		for(int i = 1; i <= n; i++) if(!dfn[i]) {
			flag = false;
			break;
		}
		if(ans == 999999999) ans = -1;
		if(ans == 0) ans = 1;
		if(!flag) {
			ans = 0;
		} 
		printf("%d\n", ans);
    }
    return 0;
}

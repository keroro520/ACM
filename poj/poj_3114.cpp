/*
	强连通  简单题

	题意：在一个有向图里面，在同一个强连通分量里面的点之间的消费为0，不在同一个强连通分量的点之间是有消费的，问从一个点到另一个点的最小消费。

	思路：缩点后求两点最短路径，记忆化/dijstra/floyd随便...这里是记忆化
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		bug(x)	printf("# %d\n", x)
#define		INF		999999999
#define		MAXN	505
int sink ;//for debug
struct Edge {
	int v, next, w;
} edge[MAXN * MAXN];
int head[MAXN], dfn[MAXN], low[MAXN], belong[MAXN], S[MAXN], f[MAXN], path[MAXN][MAXN];
bool in_stack[MAXN];
int n, edge_num, S_top, Index, Order;

void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	edge[edge_num].w = w;
	head[u] = edge_num++;
}
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
			x = S[--S_top];
			in_stack[x] = false;
			belong[x] = Order;
		} while(x != u);
		Order++;
	}
}
void init()
{
	edge_num = Order = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
}


inline void update_min(int &x, int y) {
	if(x == -1) x = y; else if(x > y) x = y;
}
int DP(int u)
{
	if(f[u] != -1) return f[u];
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		update_min(f[u], DP(v) + edge[k].w);
	}
	return f[u] = (f[u] == -1 ? INF : f[u]);
}
int main()
{
	int m, query, begin, end;
	while(scanf("%d%d", &n, &m) , n) {
		init();
		while(m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w);
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
		for(int i = 0; i < Order; i++) {
			for(int j = 0; j < Order; j++) path[i][j] = INF;
		}
		for(int u = 1; u <= n; u++)
			for(int k = head[u]; k != -1; k = edge[k].next) {
				int v = edge[k].v, x = belong[u], y = belong[v];
				if(x != y) {
					update_min(path[x][y], edge[k].w);
				}
			}
		memset(head, -1, sizeof(head));
		edge_num = 0;
		for(int i = 0; i < Order; i++)
			for(int j = 0; j < Order; j++) if(path[i][j] != INF)
				add_edge(i,j,path[i][j]);
		scanf("%d", &query);
		while(query--) {
			scanf("%d%d",  &begin, &end);
			int x = belong[begin], y = belong[end];
			if(x == y) printf("%d\n", 0);
			else {
				memset(f, -1, sizeof(int) * (Order + 1));
				f[y] = 0;
				sink = y;
				int ans = DP(x);
				if(ans >= INF) printf("Nao e possivel entregar a carta\n");
				else printf("%d\n", ans);
			}
		}
		printf("\n");
	}
	return 0;
}

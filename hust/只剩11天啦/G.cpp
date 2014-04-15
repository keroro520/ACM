#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
#define MAXN 10005
#define MAXM 100005
struct Edge {
	int v, next;
} edge[MAXM * 2];
int head[MAXN], dfn[MAXN], low[MAXN], e[MAXM][2], S[MAXN], rank[MAXN], belong[MAXN];
bool color[MAXN], ins[MAXN];
ll ans, hello;
int edge_num, Index, Order, S_top, n;

void init()
{
	edge_num = Index = Order = S_top = 0;
	memset(head, -1, sizeof head);
	memset(dfn,   0, sizeof dfn );
	memset(ins,   0, sizeof ins );
	memset(rank,  0, sizeof rank);
	memset(color, 0, sizeof color);
}
void add_edge(int  u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void Tarjan(int u, int pre)
{
	dfn[u] = low[u] = ++Index;
	S[S_top++] = u;  ins[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre) continue;
		if(!dfn[v]) { 
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		int x;
		do {
			x = S[--S_top];
			ins[x] = false;
			belong[x] = Order;
			rank[Order]++;
		} while(x != u);
		Order++;
	}
}
void dye(int u)
{
	color[u] = true;
	hello ++;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!color[v] && rank[v] == 1) dye(v);
	}
}
int main()
{
	int cases, Cas = 0, m, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &u, &v);
			add_edge(u, v), add_edge(v, u);
			e[i][0] = u, e[i][1] = v;
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i, i);
		edge_num = 0, memset(head, -1, sizeof head);
		for(int i = 0; i <  m; i++) {
			u = belong[e[i][0]], v = belong[e[i][1]];
			if(u != v) add_edge(u, v), add_edge(v, u);
		}
		ans = 0;
		for(int i = 0; i < Order; i++) if(!color[i] && rank[i] == 1) hello = 0, dye(i), ans += hello * (hello - 1) / 2;
		printf("Case #%d: %lld\n", ++Cas, ans);
	}
	return 0;
}

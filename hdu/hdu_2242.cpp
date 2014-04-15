/*
	强连通  树形DP  简单题
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	10005
#define		MAXM	40005
struct Edge {
	int v, next;
} edge[MAXM];
int head[MAXN], dfn[MAXN], low[MAXN], child[MAXN], S[MAXN], E[MAXM][2], a[MAXN], belong[MAXN];
bool in_stack[MAXN], used[MAXM];
int ans, edge_num, Order, Index, n, S_top, N;
void Update_min(int x, int &y) { y = min(x, y); }
void dfs(int u, int father)
{
	int tot = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dfs(v, u);
		tot += child[v];
//		Update_min( abs(child[v] - (n - child[v])
	}
	tot += child[u];
	Update_min( abs(tot - (N - tot)), ans);
	child[u] = tot;
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = Order = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn, 0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
	memset(child, 0, sizeof(child));
	memset(used, false, sizeof(used));
}
void Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	S[S_top++] = u;
	in_stack[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) if(!used[k]){
		used[k] = used[k^1] = true;
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
			child[Order] += a[x];
		} while(x != u);
		Order++;
	}
}
int main()
{
	int m;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		N = 0;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), N += a[i];
		int tmp = m;
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
			E[m][0] = u, E[m][1] = v;
		}
		Tarjan(0);
		if(Order == 1) {
			printf("impossible\n");
			continue;
		}
		edge_num = 0;
		memset(head, -1, sizeof(head));
		for(int i = 0; i < tmp; i++) {
			int u = belong[E[i][0]], v = belong[E[i][1]];
			if(u != v) add_edge(u, v), add_edge(v, u);
		}
		ans = 99999999;
		dfs(0, -1);
		printf("%d\n", ans);
	}
	return 0;
}

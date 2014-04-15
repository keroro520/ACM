/*
	LCA+RMQ

	//问题描述，给定一棵带边权的树，给定三个点的查询，求把他们连起来的最小代价
	//两两求得距离之和除2，联系在数轴上的三个点，是不是也这么求

	这里直接在树上求LCA，没有转成线性的RMQ
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN		50005
#define			ANC_SIZE	20
int n, edge_num;
struct Edge {
	int v, next, w;
} edge[MAXN * 2];
int anc[MAXN][ANC_SIZE], head[MAXN], depth[MAXN], dis[MAXN];

int LCA(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	int k = depth[u] - depth[v];
	for(int i = 0; i < ANC_SIZE; i++) if(k & (1 << i)) {
		u = anc[u][i];
	}
	if(u == v) return u;
	for(int i = ANC_SIZE - 1; i >= 0; i--) 
		if(anc[u][i] != anc[v][i]) 
			u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}
int Query(int u, int v)
{
	return dis[u] + dis[v] - 2 * dis[LCA(u,v)];
}
void build(int u, int fa, int dep)
{
	depth[u] = dep;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		dis[v] = dis[u] + edge[k].w;
		anc[v][0] = u;
		for(int i = 1; i < ANC_SIZE; i++) 
			anc[v][i] = anc[anc[v][i-1]][i-1];
		build(v, u, dep+1);
	}
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(anc, -1, sizeof(anc));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
int main()
{
	int u, v, w, x, y, z, query;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		dis[1] = 0;
		build(0, -1, 0);
		scanf("%d", &query);
		while(query--) {
			scanf("%d%d%d", &x, &y, &z);
			printf("%d\n", (Query(x, y) + Query(y, z) + Query(z, x))/2);
		}
		puts("");
	}
	return 0;
}

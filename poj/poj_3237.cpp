/*
	一道LCA + 树转线性结构的好题  ....   被用爬山坡水过了 ....
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	10005*2
struct Edge {
	int v, next, w;
} edge[MAXN * 4];
int fa[MAXN], depth[MAXN], p[MAXN], weight[MAXN], head[MAXN];
int n, edge_num;
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void build(int u, int father)
{
	for(int k = head[u]; k!= -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		depth[v] = depth[u] + 1;
		p[k/2+1] = v;
		weight[v] = edge[k].w;
		fa[v] = u;
		build(v, u);
	}
}
void Update(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	while(depth[u] != depth[v]) {
		weight[u] = -weight[u];
		u = fa[u];
	}
	while(u != v) {
		weight[u] = -weight[u], weight[v] = -weight[v];
		u = fa[u],    v = fa[v];
	}
}
int Query(int u, int v)
{
	int ans = -999999999;
	if(depth[u] < depth[v]) swap(u, v);
	while(depth[u] != depth[v]) {
		ans = max(ans, weight[u]);
		u = fa[u];
	}
	while(u != v) {
		ans = max(ans, max(weight[u], weight[v]));
		u = fa[u], v = fa[v];
	}
	return ans;
}
int main()
{
	int cases, w, u, v, x, y;
	char op[10];
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		depth[1] = 0, fa[1] = 0;
		build(1, 0);
		while(scanf("%s", op), op[0] != 'D') {
			scanf("%d%d", &x, &y);
			if(op[0] == 'C') weight[ p[x] ] = y;
			else if(op[0] == 'N') Update(x, y);
			else if(op[0] == 'Q') printf("%d\n", Query(x, y));
		}
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN		100005
struct Edge {
	int v, next, w;
} edge[MAXN * 2];
int head[MAXN];
int n, S, edge_num;
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
void init()
{
	edge_num = Time = 0;
	memset(head, -1, sizeof(head));
}
void build(int u, int fa)
{
	in[u] = Time++;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		build(v, u);
	}
	out[u] = Time-1;
}
int main()
{
	int query, u, v, w;
	while(scanf("%d%d%d", &n, &query, &S) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		build(1, 0);
	}
	return 0;
}

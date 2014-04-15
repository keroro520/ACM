#include <stdio.h>
#include <string.h>
#define		MAXN	1005
#define		MAXM	10005*2
#define		INF		9999999
#define		Limit	1005*20
struct Edge {
	int v, next, w;
} edge[MAXM * 2];
int head[MAXN], val[MAXN], dis[MAXN], girl[MAXN], Q[Limit];
bool vis[MAXN];
int n, m, edge_num;
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
void init()
{	
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void SPFA(int s, int t)
{
	for(int i = 2; i <= n; i++) dis[i] = INF;
	memset(vis, false, sizeof(vis));
	memset(val, 0, sizeof(val));
	dis[s] = 0, val[s] = girl[s];
	int car = 1, cdr = 0;
	Q[1] = s;
	while(car != cdr) {
		cdr++;
		if(cdr == Limit) cdr = 0;
		int u = Q[cdr];
		vis[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(dis[u] + edge[k].w < dis[v]) {
				dis[v] = dis[u] + edge[k].w;
				val[v] = val[u] + girl[v];
				if(!vis[v]) {
					car++;
					if(car == Limit) car = 0;
					Q[car] = v;
					vis[v] = true;
				}
			} else if(dis[u] + edge[k].w == dis[v] && val[u] + girl[v] > val[v]) {
				val[v] = val[u] + girl[v];
				if(!vis[v]) {
					car++;
					if(car == Limit) car = 0;
					Q[car] = v;
					vis[v] = true;
				}
			}
		}
	}
}
int main()
{
	int u, v, w;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &girl[i]);
		for(int i = 0; i < m; i++) {	
			scanf("%d%d%d", &u, &v, &w);
			if(u == v) continue;
			add_edge(u, v, w), add_edge(v, u, w);
		}
		SPFA(1, n);
		if(dis[n] == INF) printf("-1\n");
		else printf("%d\n", val[n]);
	}
	return 0;
}

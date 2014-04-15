/*
	博弈论 简单题 SG
*/
#include <stdio.h>
#include <string.h>
#define		MAXN	1005
struct Edge {
	int v, next;
} edge[MAXN * MAXN];
int head[MAXN], sg[MAXN];
int n, edge_num;

int SG(int u)
{
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(bool) * (n+1));
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		vis[SG(v)] = true;
	}
	for(int i = 0; i < n; i++) if(!vis[i]) return sg[u] = i;
	return sg[u] = 0;
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
	memset(head, -1, sizeof(head));
	memset(sg,   -1, sizeof(sg));
}
int main()
{
	int j, many, query;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%d", &many);	
			while(many--) {
				scanf("%d", &j);
				add_edge(i, j);
			}
		}
		while(scanf("%d", &query), query) {
			int ans = 0;
			while(query--) {
				scanf("%d", &j);
				ans ^= SG(j);
			}
			printf("%s\n", ans ? "WIN" : "LOSE");
		}
	}
	return 0;
}

/*
	树的最长链
	为什么数论场会有树的最长链？ 为什么在VJ上交死活RE到POJ交就AC？？？？？
*/
#include <stdio.h>
#include <string.h>
struct Edge {
	int v, w, next;
} edge[100005 * 2];
int head[100005], end, ans, edge_num;
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void dfs(int u, int d, int pre)
{
	if(ans <= d) ans = d, end = u;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v != pre) dfs(v, d+edge[k].w, u);
	}
}
int main()
{
	int u, v, w;
	memset(head, -1, sizeof(head));
	while(scanf("%d %d %d", &u, &v, &w) != EOF) {
		if(u == v) continue;
		add_edge(u, v, w), add_edge(v, u, w);
	}
	//if(edge_num == 0) { puts("0"); return 0; }
	dfs(1, 0, 1);
	ans = 0;
	dfs(end, 0, end);
	printf("%d\n", ans);
	return 0;
}

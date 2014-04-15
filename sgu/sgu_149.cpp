/*
	树状DP  树的直径
	题意：给一棵树，问每个点到其余点的最远距离。

	思路：求出直径上的两个端点，然后从这两个端点bfs或dfs更新一下每个点的val[]就可以了。

		  G-rate用的树状DP做，感觉好高端，而且也比较有通用性。
*/
//sgu 149
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
int head[MAXN], val[MAXN];
struct Edge {
	int v, next, w;
} edge[MAXN * 2];
int n, edge_num, Max_len, end;
void dfs(int u, int father, int dis)
{
	if(dis > Max_len) Max_len = dis, end = u;
	val[u] = max(val[u], dis);
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dfs(v, u, dis+edge[k].w);
	}
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(val, 128, sizeof(val));
	memset(head, -1, sizeof(head));
}
int main()
{
	int u, w;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 2; i <= n; i++) {
			scanf("%d%d", &u, &w);
			add_edge(u, i, w), add_edge(i, u, w);
		}
		Max_len = -1;
		dfs(1, 1, 0);
		Max_len = -1;
		dfs(end, end, 0);
		Max_len = -1;
		dfs(end, end, 0);
		for(int i = 1; i <= n; i++) printf("%d\n", val[i]);
	}
	return 0;
}

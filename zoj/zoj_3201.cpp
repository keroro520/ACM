/*
	树DP  递推
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	105
struct Edge {
	int v, next;
} edge[MAXN * 2];
int head[MAXN], f[MAXN][MAXN], n, edge_num, m, ans;

void dfs(int u, int father)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dfs(v, u);
		for(int j = m; j > 1; j--)				//u点必须选
			for(int i = 1; i < j; i++)
				f[u][j] = max(f[u][j], f[v][j-i] + f[u][i]);
	}
	ans = max(ans, f[u][m]);
}
int main()
{
	int u, v;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		for(int i = 0; i < n; i++) scanf("%d", &f[i][1]);
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		ans = -999999;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(f, 0, sizeof(f));
	for(int i = 0; i < n; i++) f[i][0] = 0;
}

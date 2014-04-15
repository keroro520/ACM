/*
	图上的动态规划
	1Y
*/
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct Edge {
	int v, next;
} edge[5000 * 2];
int f[205][105], a[205], head[205];
int len, n, m, edge_num;
void add_edge(int u, int v)
{	
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int main()
{
	int cases, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		edge_num = 0, memset(head, -1, sizeof head);
		while(m--) {
			scanf("%d %d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		for(u = 1; u <= n; u++) add_edge(u,u);
		scanf("%d", &len);
		for(int i = 1; i <= len; i++) scanf("%d", &a[i]);
		memset(f, 127, sizeof f);
		memset(f[0], 0, sizeof f[0]);
		for(int i = 1; i <= len; i++)
			for(u = 1; u <= n; u++) {
				for(int k = head[u]; k != -1; k = edge[k].next) {
					v = edge[k].v;
					f[i][u] = min(f[i][u], f[i-1][v] + (u != a[i]));
				}
			}
		int ans = len;
		for(u = 1; u <= n; u++) ans = min(ans, f[len][u]);
		printf("%d\n", ans);
	}
	return 0;
}

/*
	还好吧，读错题意而已，不然AC还是不难的。
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define	 MAXN 3005
struct Edge {
	int v, a, b, next;
} edge[MAXN * 2];
int head[MAXN], f[MAXN];
int low, n, edge_num, when;
int ans = 0;
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof head);
}
void add_edge(int u, int v, int a, int b)
{
	edge[edge_num].v = v, edge[edge_num].a = a, edge[edge_num].b = b;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void solve(int u, int high)
{
	if(high <= f[u] || high - low + 1 <= ans) return ;
	f[u] = high;
	for(int k = head[u]; k != -1; k = edge[k].next) if(edge[k].a <= low && low <= edge[k].b) {
		int v = edge[k].v;
		solve(v, min(high, edge[k].b));
	}
}
int main()
{
	int u, v, a, b, m, inf = 999999999;
	scanf("%d %d", &n, &m);
	init();
	for(int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &u, &v, &a, &b);
		add_edge(u, v, a, b), add_edge(v, u, a, b);
	}
	for(int i = 0; i < edge_num; i += 2) {
		low = edge[i].a;
		when++;
		for(int i = 1; i <= n; i++) f[i] = -inf;
		solve(1, inf);
		if(f[n] != -inf) ans = max(ans, f[n] - low + 1);
	}
	if(ans == 0) puts("Nice work, Dima!");
	else printf("%d\n", ans);
	return 0;
}

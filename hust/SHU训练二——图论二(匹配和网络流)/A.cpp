/*
	图论 二分图最大匹配 简单题
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		105
struct Edge {
	int v, next;
} edge[MAXN * MAXN];
int head[MAXN], a[MAXN], b[MAXN], vis[MAXN + MAXN], link[MAXN + MAXN];
int m, n, edge_num, when;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void build()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= m; j++)
			if(b[j] % a[i] == 0) add_edge(i, j+n);
}
bool Find(int u)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(vis[v] == when) continue;
		vis[v] = when;
		if(link[v] == -1 || Find(link[v])) {
			link[v] = u;
			return true;
		}
	}
	return false;
}
int  max_match()
{
	int ans = 0;
	memset(link, -1, sizeof(link));
	for(int i = 1; i <= n; i++) {
		when++;
		ans += Find( i );
	}
	return ans;
}
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);  for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		scanf("%d", &m);  for(int i = 1; i <= m; i++) scanf("%d", &b[i]);
		build();
		int ans = max_match();
		printf("Case %d: %d\n", ++Cas, ans);
	}
	return 0;
}

#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN		10005
int vis[MAXN], head[MAXN], color[MAXN], zombie[MAXN];
int edge_num , when;
struct Edge {
	int v, next;
} edge[MAXN * 2];

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
	memset(color, 0, sizeof(color));
}
void dye(int u, int d)
{
	if(d < 0) return ;
	vis[u] = when;
	color[u] ++ ;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(vis[v] != when) dye(v, d-1);	
	}	
}
int main()
{
	int n, m, D, x, y;
	while(scanf("%d%d%d", &n, &m, &D) != EOF) {
		init();
		for(int i = 0; i < m; i++) scanf("%d", &zombie[i]);
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &x, &y);
			add_edge(x, y);
			add_edge(y, x);
		}
		for(int i = 0; i < m; i++) {
			++when;
			dye(zombie[i], D);
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += (color[i] == m);
		printf("%d\n", ans);
	}
	return 0;
}

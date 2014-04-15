#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXM	50005
#define		MAXN	1005
struct Edge {
	int u, v, next, w;
} edge[MAXM * 2];
int  head[MAXN], dis[MAXN], S[MAXN], hello[MAXN];
bool vis[MAXN];
int edge_num, n, inf, del, del2, ans;

void init()
{
	edge_num = 0;
	del = del2 = -1;
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].u = u; edge[edge_num].v = v; edge[edge_num].w = w;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void SPFA(int s, int t)
{
	memset(vis, false, sizeof(vis));
	memset(dis, 127,   sizeof(dis));
	int top = 0;
	S[top++] = s;
	dis[s] = 0;
	while(top) {
		int u = S[--top];
		vis[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) if(k != del && k != del2){
			int v = edge[k].v, w = edge[k].w;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if(!vis[v]) vis[v] = true, S[top++] = v;
			}
		}
	}
}
void reverse_and_update(int u)
{
	if(u == 1) return ;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v, w = edge[k].w;
		if(hello[v] + w == hello[u]) {
			del = k, del2 = k^1;
			SPFA(1, n);
			ans = max(ans, dis[n]);
			reverse_and_update(v);
		}
	}
}
int main()
{
	int cases, u, v, w, m;
	memset(&inf, 127, sizeof(inf));
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		SPFA(1, n);
		if(dis[n] == inf) { puts("-1"); continue ; }
		for(int i = 1; i <= n; i++) hello[i] = dis[i];
		ans = 0;
		reverse_and_update(n);
		if(ans == inf) { puts("-1"); continue ; }
		else	printf("%d\n", ans);
	}
	return 0;
}

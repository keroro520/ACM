/*
	拓扑  并查集  

	题意：给一个有向图G，问最少要取多少个起点，从这些起点开始可以遍历整个图。

	思路：入度为零的点必定为起点。
		  环内的点，且环不与图G的其它部分有交集，随便选一个做起点。
		  我写的时候只考虑了上面两种情况。WA了，看forum知道还有第三种情况。如下面数据：
		  (6,7) (2,5) (4,1) (5,2) (5,3) (5,4) (5,6) (6,5) 	答案应该是1

		  即环与图G其它部分有交集。所以加了并查集对付第3种情况。
*/
//lightoj 1034
#include <stdio.h>
#include <string.h>
#define		MAXN	10005
#define		MAXM	100005
struct Edge {
	int v, next;
} edge[MAXM];
int head[MAXN], in_deg[MAXN], Q[MAXN], father[MAXN];
int n, edge_num;
bool vis[MAXN];

void init()
{	
	edge_num = 0;
	memset(in_deg, 0, sizeof(in_deg));
	memset(vis, false, sizeof(vis));
	memset(head, -1, sizeof(head));
	for(int i = 0;  i <= n; i++) father[i] = i;
}
void bfs(int s)
{
	int top = 0, tail = 0;
	Q[top++] = s;
	vis[s] = true;
	while(tail < top) {
		int u = Q[tail++];
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(!vis[v]) {	
				Q[top++] = v;
				vis[v] = true;
			}
		}
	}
}
int Find(int x) { return x == father[x] ? x : father[x] = Find(father[x]); }
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
	father[Find(v)] = Find(u);
}
int main()
{
	int cases, Cas = 0, m, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		init();
		while(m--) {
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			in_deg[v] ++;
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) if(!vis[i] && in_deg[i] == 0) bfs(i), ans ++ ;
		for(int i = 1; i <= n; i++) if(!vis[i]) bfs(Find(i)), ans ++ ;
		printf("Case %d: %d\n", ++Cas, ans);
	}
	return 0;
}

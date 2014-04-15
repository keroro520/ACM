/*
	LCA 离线
	写第二遍，没有参考1A了。	我是比较喜欢这个版本。
*/
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define			MAXN			40005
typedef		pair<int,int> PII 	;
vector< PII > Quetion[MAXN];
int head[MAXN], dis[MAXN], father[MAXN], ans[500];
bool vis[MAXN];
struct Edge {
	int v, next, w;
} edge[MAXN * 2];
int n, edge_num;

void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v;
	edge[edge_num].w = w;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	for(int i = 0; i <= n; i++) Quetion[i].clear();
	memset(vis, false, sizeof(vis));
	for(int i = 0; i <= n; i++) father[i] = i;
}
void build(int u, int fa)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		dis[v] = edge[k].w + dis[u];
		build(v, u);
	}
}
int Find(int x) { return x == father[x] ? x : father[x] = Find(father[x]); }
void Union(int x, int y) { father[x] = y; }
void LCA(int u, int fa)
{
	vis[u] = true;
	for(int Size = Quetion[u].size(), i = 0; i < Size; i++) {
		int v = Quetion[u][i].first;
		if(!vis[v]) continue;
		ans[ Quetion[u][i].second ] = dis[v] + dis[u] - 2 * dis[ Find(v) ];
	}
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(fa == v) continue;
		LCA(v, u);
	}
	Union(u, fa);
}
int main()
{
	int cases, u, v, query, w;

	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &query);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		dis[1] = 0;
		build(1, 0);
		for(int i = 0; i < query; i++) {
			scanf("%d%d", &u, &v);
			Quetion[u].push_back( PII(v, i) );
			Quetion[v].push_back( PII(u, i) );
		}
		LCA(1, 0);
		for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
	}
	return 0;
}

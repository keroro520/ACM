/*
	LCA  离线
	题意：就是问有向图里两个点的最小公共祖先啦。
	这才是真正的poj_1470，另一个博弈的代码是啥？
*/
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define		MAXN	905
inline		char	rdc()	{scanf(" "); return getchar() ; }
struct Edge {
	int v, next;
} edge[MAXN];
int head[MAXN], father[MAXN], query_times[MAXN];
bool in_deg[MAXN], vis[MAXN];
vector<int> Quetion[MAXN];
int n, edge_num;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(query_times, 0, sizeof(query_times));
	memset(in_deg, false, sizeof(in_deg));
	memset(vis, false, sizeof(vis));
	for(int i = 0; i <= n; i++) father[i] = i;
	for(int i = 0; i <= n; i++) Quetion[i].clear();
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int Find(int x) { return x == father[x] ? x : father[x] = Find(father[x]) ; }
void Union(int x, int y) { father[x] = y; }

void LCA(int u, int fa)
{
	vis[u] = true;
	for(int Size = Quetion[u].size(), i = 0; i < Size; i++) {
		int v = Quetion[u][i];
		if(!vis[v]) continue;
		query_times[ Find(v) ] ++;
	}
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		LCA(v, u);
	}
	Union(u, fa);
}
int main()
{
	int u, v, k, query;
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%d", &u);
			rdc(), rdc();
			scanf("%d", &k);
			rdc();
			for(int j = 0; j < k; j++) {
				scanf("%d", &v);
				add_edge(u, v);
				in_deg[v] = true;
			}
		}
		scanf("%d", &query);
		for(int i = 0; i < query; i++) {
			rdc(), scanf("%d %d", &u, &v), rdc();
			Quetion[u].push_back( v );
			Quetion[v].push_back( u );
		}
		for(int i = 1; i <= n; i++) if(!in_deg[i]) {
			LCA(i, 0);
			break;
		}
		for(int i = 1; i <= n; i++) if(query_times[i]) printf("%d:%d\n", i, query_times[i]);
	}
	return 0;
}

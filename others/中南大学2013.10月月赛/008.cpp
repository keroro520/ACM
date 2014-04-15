/*
	并查集 + 分组背包
*/
//http://acm.csu.edu.cn/OnlineJudge/problem.php?cid=2037&pid=8
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define		debug		printf("!\n")
#define		MAXN		1005
vector<int> v[MAXN];
struct Edge {
	int v, next;
} edge[MAXN*2];
int head[MAXN], price[MAXN], val[MAXN], f[MAXN][MAXN], fa[MAXN];
bool vis[MAXN];
int edge_num, n, m, K;
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n; i++) fa[i] = i, v[i].clear();
	memset(f, 0, sizeof(f));
}
int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }
void Union(int u, int v)
{
	int fx = Find(u), fy = Find(v);
	if(fx != fy) {
		fa[fy] = fx;
	}
}
void dfs(int u, int pre, int anc)
{
	Union(anc, u);
	vis[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre || vis[v] ) continue;
		dfs(v, u, anc);
	}
}
int main()
{
	int x, y;
	while(scanf("%d%d%d", &n, &m, &K) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d%d", &val[i], &price[i]);
		for(int i = 0; i < K; i++) {
			scanf("%d%d", &x, &y);
			if(x == y) continue;
			add_edge(x, y), add_edge(y, x);
		}
		for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, i, i);
		memset(vis, false, sizeof(vis));
		int idx = 0;
		for(int i = 1; i <= n; i++) v[Find(i)].push_back(i);
		for(int i = 1; i <= n; i++) if(!vis[Find(i)]) {
			idx++;
			int father = Find(i);
			vis[father] = true;
			for(int j = m; j >= 0; j--) f[idx][j] = f[idx-1][j];
			for(int j = m; j >= 0; j--)
				for(vector<int> :: iterator it = v[father].begin(); it != v[father].end(); it++) 
					if(j >= price[*it]) f[idx][j] = max(f[idx][j], f[idx-1][j-price[*it]] + val[*it]);
		}
		printf("%d\n", f[idx][m]);
	}
	return 0;
}

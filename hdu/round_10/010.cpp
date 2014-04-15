#pragma comment(linker, "/STACK:16777216")
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define		MAXN	100005
int edge_num; 
long long n;
//vector<int> adj[MAXN];
long long ans;
long long child[MAXN];
int head[MAXN];
struct Edge {
	int v, next;
} edge[MAXN * 2];

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(child,   0, sizeof(child));
//	for(int i = 0; i <= n; i++) adj[i].clear();
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void dfs(int u, int father)
{
	long long  tot = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		dfs(v, u);
		ans += tot * (child[v] + 1);
		tot += child[v] + 1;
	}
	child[u] = tot;
	ans += tot * (n - 1 - tot);
}
int main()
{
	int x, y;
	while(scanf("%I64d", &n) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &x, &y);
			add_edge(x, y);
			add_edge(y, x);
		}
		ans = 0;
		dfs(1, 0);
		printf("%I64d\n", n*(n-1)*(n-2)/6 - ans);
	}
	return 0;
}

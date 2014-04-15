#include <string.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;
#define			MAXN		10005
struct Edge {
	int v, next;
} edge[MAXN];
int head[MAXN], fa[MAXN];
bool vis[MAXN];
vector<int> child[MAXN];
int n, edge_num ;

void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	memset(vis, false, sizeof(vis));
	edge_num = 0;
	memset(head, -1, sizeof(head));
	for(int i = 0; i < n; i++) child[i].clear();
}
int dfs(int u)
{
	vis[u] = true;
	if(head[u] == -1) return 1;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(vis[v]) return -1;
		int res = dfs(v);
		if(res == -1) return -1;
		child[u].push_back( res );
	}
	sort(child[u].begin(), child[u].end());
	int sum = 1;
	for(int Size = child[u].size(), i = 0; i < Size; i++) {
		if(child[u][i] > sum) return -1;
		sum += child[u][i];
	}
	return sum;
}

int main()
{
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 0; i < n; i++) {
			scanf("%d", &fa[i]);
			if(fa[i] != i) add_edge(fa[i], i);
		}
		bool flag = true;
		for(int i = 0; i < n; i++) if(fa[i] == i) {
			if(dfs(i) == -1) {
				flag = false;
				break;
			}
		}
		for(int i = 0; i < n; i++) if(!vis[i]) flag = false;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}

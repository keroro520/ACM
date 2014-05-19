#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
#define		MAXN		100005

struct Edge {
	int v, next;
} edge[MAXN * 2];
int n, edge_num, head[MAXN], color[MAXN], goal[MAXN];
vector<int> ans;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof head);
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void dfs(int u, int a, int b, int father)		//a是影响u的, b是不影响u的
{
	if (a) {
		if ((color[u] ^ 1) != goal[u]) ans.push_back(u), a ^= 1;
	} else {
		if (color[u] != goal[u]) ans.push_back(u), a ^= 1;
	}

	for (int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if (v == father) continue;
		dfs(v, b, a, u);
	}
}
int main()
{
	int u, v;
	scanf("%d", &n);
	init();
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &goal[i]);
	dfs(1, 0, 0, -1);
	printf("%d\n", ans.size());
	for (auto it = ans.begin(); it != ans.end(); it ++) printf("%d\n", *it);
	return 0;
}

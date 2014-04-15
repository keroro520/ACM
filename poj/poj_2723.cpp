/*
	2-SAT  二分求最优

	题意：给出 n 对钥匙，每对只能挑一把使用，每把只能用一次，当一对钥匙中的一把被使用后，另一把也就不能再用了；然后给出 m 道门，每个门都有两把钥匙可以打开，问最多能开几道门（按给出的顺序开）

	思路：    对于一扇门所需钥匙(x,y)，它们的矛盾关系边应该是什么呢？因为“每扇门有两把钥匙可以打开”，并且“一定要其中一把钥匙”，所以，矛盾边应该是x'--y'，即表示钥匙x和钥匙y都没选取到(x'表没有选x)
			二分答案，2-sat验证
	http://blog.csdn.net/l04205613/article/details/6670249
*/

#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define			MAXN		(1 << 13)
struct Edge {
	int v, next;
} edge[MAXN * MAXN];
int head[MAXN], dfn[MAXN], low[MAXN], belong[MAXN], a[MAXN][2], b[MAXN][2], S[MAXN];
bool in_stack[MAXN];
int n, edge_num, Order, Index, S_top;

inline	int hash(int x) { return x + 2*n; }
void Tarjan(int u)
{
	low[u] = dfn[u] = Index++;
	S[S_top++] = u;
	in_stack[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		int x ;
		do {
			x = S[--S_top];
			in_stack[x] = false;
			belong[x] = Order;
		} while(u != x);
		Order++;
	}
}

void init()
{
	edge_num = S_top = Order = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void build(int bound)
{
	for(int i = 0; i < n; i++) {
		add_edge(a[i][0], hash(a[i][1])), add_edge(a[i][1], hash(a[i][0]));
	}
	for(int i = 0; i < bound; i++) {
		add_edge(hash(b[i][0]), b[i][1]), add_edge(hash(b[i][1]), b[i][0]);
	}
}
bool check(int bound)
{
	init();
	build(bound);
	for(int i = 0; i < 2*n; i++) if(!dfn[i]) Tarjan(i);
	for(int i = 0; i < 2*n; i++) if(belong[i] == belong[hash(i)]) return false;
	return true;
}

int main()
{
	int m;
	while(scanf("%d%d", &n, &m) != EOF && n && m) {
		for(int i = 0; i < n; i++) scanf("%d%d", &a[i][0], &a[i][1]);
		for(int i = 0; i < m; i++) scanf("%d%d", &b[i][0], &b[i][1]);
		int l = 0, r = m, ans = -1, mid;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

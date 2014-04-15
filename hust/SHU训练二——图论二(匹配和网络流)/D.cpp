/*
	WA
	bin神给了我个数据，确实说明我的解法是错的。
	(1,2) (1,3) (2,4) (3,4)
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define			MAXN		1005
#define			MAXM		10005

vector<int> adj[MAXN];
struct Edge {
	int v, next;
} edge[MAXM];
int  head[MAXN], vis[MAXN], dfn[MAXN], S[MAXN], low[MAXN], belong[MAXN], e[MAXM][2], link[MAXN];
bool ins[MAXN], in[MAXN], out[MAXN];
int  n, edge_num, Index, Order, S_top, when, ancester;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = S_top = Index = Order = 0;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(low,   0, sizeof(low));
	memset(vis,   0, sizeof(vis));
	memset(ins, false, sizeof(ins));
	memset(in,  false, sizeof(in));
	memset(out, false, sizeof(out));
}
void Tarjan(int u)
{
	low[u] = dfn[u] = ++Index;
	S[S_top++] = u;
	ins[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		int x;
		do {
			x = S[--S_top];
			ins[x] = false;
			belong[x] = Order;
		} while(x != u);
		Order++;
	}
}
bool Find(int u)
{
	for(vector<int> :: iterator it = adj[u].begin(); it != adj[u].end(); it++) {
		int v = *it;
		if(vis[v] == when) continue;
		vis[v] = when;
		if(link[v] == -1 || Find(link[v])) {
			link[v] = u;
			return true;
		}
	}
	return false;
}
int  max_match(int n)
{
	int ans = 0;
	memset(link, -1, sizeof(link));
	for(int i = 0; i < n; i++) if(!in[i]) {
		when++;
		ans += Find( i );
	}
	return ans;
}
void dfs(int u)
{
	if(!out[u]) adj[ancester].push_back( u );

	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!ins[v]) ins[v] = true, dfs(v);
	}
}
int main()
{
	int Cas = 0, cases, u, v, m;
	scanf("%d", &cases);
	while(cases--) {
		init();
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= m; i++) {
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			e[i][0] = u, e[i][1] = v;
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
		//for(int i = 1; i <= n; i++) printf("! %d  %d\n", i, belong[i]);
		edge_num = 0;
		memset(head, -1, sizeof(head));
		for(int i = 1; i <= m; i++) {
			u = belong[e[i][0]], v = belong[e[i][1]];
			if(u == v) continue;
			add_edge(u, v);
			out[u] = in[v] = true;
		}
		int zero_in = 0, zero_out = 0;
		for(int i = 0; i < Order; i++) zero_in += (!in[i]), zero_out += (!out[i]);

		for(int i = 0; i < Order; i++) if(!in[i]) {
			memset(ins, false, sizeof(ins));
			ancester = i, adj[i].clear(); 
			dfs(i);
			//printf("$ %d:", i);
			//for(vector<int> :: iterator it = adj[i].begin(); it != adj[i].end(); it++) printf("%d " , *it); puts("");
		}
		int ans = max_match(Order);
		ans = zero_in + zero_out - ans;

		printf("Case %d: %d\n", ++Cas, ans);
	}
	return 0;
}

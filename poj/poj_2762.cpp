/*
	连通性  经典题
	题意：判断一个有向图是否弱连通，即对于任意两点(u,v)存在一条路径使得u能到达v或者v能到达u

	思路：缩点+判单链
		  缩点后如果有两个或两个以上的点出度为0或者入度为0，则false
		  缩点后的图是不是单链。如果不是单链，即有分叉，则根据缩点后的图的性质可知，两个分叉上的点不能到达，false

		  判单链可以暴力dfs，可以拓扑排序，可以DP最长链。我写了前面两种。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <deque>
using namespace std;
#define		MAXN	1005
#define		MAXM	6005
struct Edge {
	int v, next, u;
} edge[MAXM], e[MAXM];
int head[MAXN], S[MAXN], dfn[MAXN], low[MAXN], in_deg[MAXN], belong[MAXN];
bool in_stack[MAXN];
bool pass[MAXN];
int Order, Index, edge_num, n, S_top;

void init()
{
	Index = 1;
	edge_num = Order = S_top = 0;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
}
void init2()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(in_deg, 0, sizeof(in_deg));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].u = u, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	in_stack[u] = true;
	S[S_top ++ ] = u;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		int x;
		do {
			x = S[--S_top];
			in_stack[x] = false;
			belong[x] = Order;
		} while(x != u) ;
		Order ++ ;
	}
}
bool Topsort()
{
	deque<int> Q;
	int cnt = 0;
	for(int i = 0; i < Order; i++) 
		if(in_deg[i] == 0) cnt++, Q.push_back(i);
	if(cnt > 1) return false;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop_front();
		cnt = 0;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(in_deg[v] && (--in_deg[v] == 0)) {
				Q.push_back(v);
				cnt ++;
			}
		}
		if(cnt > 1) return false;
	}
	return true;
}
void dfs(int u);
int main()
{
	int cases, m, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			e[i].u = u, e[i].v = v;
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
		init2();
		for(int i = 0; i < m; i++) {
			u = e[i].u, v = e[i].v;
			if(belong[u] == belong[v]) continue;
			add_edge(belong[u], belong[v]);
			in_deg[ belong[v] ]++;
		}
		if(Order == 1) {
			puts("Yes");
			continue;
		}

		memset(pass, false, sizeof(pass));
		for(int i = 0; i < Order; i++) if(in_deg[i] == 0) {
			dfs(i);
			break;
		}
		bool flag = true;
		for(int i = 0; i < Order; i++) if(!pass[i]) flag = false;
		puts(flag ? "Yes" : "No");
		//puts( Topsort() ? "Yes" : "No");			//第一种方法判单链
	}
	return 0;
}
void dfs(int u)
{
	pass[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		dfs(v);
		return;
	}
}

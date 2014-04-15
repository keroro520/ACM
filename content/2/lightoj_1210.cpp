/*
	强连通 简单题
	经典水题竟然WA了3次。。。
*/
//light 1210
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN	20005
#define		MAXM	50005
struct Edge {
	int v, next;
} edge[MAXM];
int edge_num, Index, Order, S_top, n;
int head[MAXN], dfn[MAXN], low[MAXN], in_deg[MAXN], out_deg[MAXN], belong[MAXN], S[MAXN];
bool in_stack[MAXN];

void init()
{
	edge_num = 0;
	Index = 1;
	Order = 0;
	S_top = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
	memset(in_deg,  0, sizeof(in_deg));
	memset(out_deg, 0, sizeof(out_deg));
	memset(head, -1, sizeof(head));
}
void Tarjan(int u)
{
	dfn[u] = low[u] = Index++;
	S[S_top++] = u;
	in_stack[u] = true;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		int x;
		do {
			x = S[--S_top];
			in_stack[x] = false;
			belong[x] = Order;
		} while(x != u);
		Order++;
	}
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
int main()
{
	int cases, Cas = 0, u, v, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		init();
		while(m--) {
			scanf("%d%d", &u, &v);
			add_edge(u, v);
		}
		for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
		for(int i = 1; i <= n; i++) 
			for(int k = head[i]; k != -1; k = edge[k].next) {
				int j = edge[k].v;
				if(belong[i] == belong[j]) continue;
				out_deg[belong[i]] ++, in_deg[belong[j]] ++;
			}
//		int ans = 0;
		int sum1 = 0, sum2 = 0;
	//	for(int i = 1; i  <= n; i++) printf("# %d %d\n", i, belong[i]);
		for(int i = 0; i < Order; i++) {
			//ans += (in_deg[i] == 0) + (out_deg[i] == 0);
			sum1 += (in_deg[i] == 0);
			sum2 += (out_deg[i] == 0);
		}
	//		if(in_deg[i] == 0) printf("in_deg[%d] == 0\n", i);
	//		if(out_deg[i] == 0) printf("out_deg[%d] == 0\n", i);
	//	}
		//if(Order == 1) ans = 0;
		if(Order == 1) printf("Case %d: 0\n", ++Cas);
		else printf("Case %d: %d\n", ++Cas, max(sum1, sum2));//(ans+1) / 2);
	}
	return 0;
}

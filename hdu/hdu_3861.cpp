/*
	二分匹配  最小路径覆盖
	想了dfs搞，没搞出来
	
	题意：有向图如果2个点可以互达，那么它们属于一个state，然后将图分割成尽量少的部分，在一个部分内，任意2点u，v，都要满足u可达v或者v可达u。

	思路：	
	1.求一次强连通分量，然后重新建图变成一个DAG
	2.DAG中一个大点内的小点一定是满足[ u可达v或者v可达u ]，另外如果是在DAG中找一条不分叉的路径，路径上的点也全部满足[ u可达v或者v可达u ]，但是分叉了就不行了。这其实就是最小路径覆盖
	最小路径覆盖：用尽量少的不想交的简单路径覆盖有向无环图的所有顶点。
	最小路径覆盖 = 顶点数 – 匹配数
	3.在DAG上做一次最大匹配求得最大匹配，从顶点数减去即可


	变化：题目可以理解为，对于一个有向图，最少需要多少条链可以覆盖整个图？而且这些链不能相交。那就是最小路径覆盖。
		  那要改为链可以相交呢？我觉得就是max(入度为0的点数，出度为0的点数)，证明略.
*/
//hdu 3861
#include <stdio.h>
#include <string.h>
#include <deque>
using namespace std;
#define		MAXN		5005
struct Edge {
	int v, next, u;
} edge[100005], e[100005];
deque<int> Q;
int head[MAXN], dfn[MAXN], low[MAXN], S[MAXN], in_deg[MAXN], belong[MAXN], link[MAXN*2];
bool in_stack[MAXN], vis[MAXN * 2];
int n, edge_num, S_top, Index, Order, ans;

void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
	S[S_top++] = u;
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(dfn[v] == 0) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
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
void init()
{
	edge_num = Order = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(in_stack, false, sizeof(in_stack));
	memset(in_deg, 0, sizeof(in_deg));
}
void add_edge(int u, int v)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num ++;
}
bool find(int u)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(vis[v]) continue;
		vis[v] = true;
		if(link[v] == -1 || find(link[v])) {
			link[v] = u;
			return true;
		}
	}
	return false;
}
int  hungary(int n)
{
	int sum = 0;
	memset(link, -1, sizeof(link));
	for(int i = 0; i < n; i++) {
		memset(vis, false, sizeof(vis));
		sum += find(i);
	}
	return sum;
}
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
		memset(head, -1, sizeof(head));
		edge_num = 0;
		for(int i = 0; i < m; i++) {
			u = e[i].u, v = e[i].v;
			if(belong[u] == belong[v]) continue;
			add_edge(belong[u], belong[v]+Order);
		}
		printf("%d\n", Order - hungary(Order));
	}
	return 0;
}

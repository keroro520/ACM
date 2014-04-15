/*
	连通性  树DP  树的构造   好题
	题意：给定一个连通的无向图，你只能毁掉一条边，而敌人可以补回一条边（但不会补你毁的那条，是任意地补另外一条）。为了保证你一定能使这个图断裂，你至少需要多少钱。即求出一个最小权值使得任意加一条边后都能去掉一条小于这个权值的边，使得图不连通。

	思路：对于缩点后的树选取出边权最小的边，分别以该边的两个端点作为根确立两个不相交的树。然后在这两个树种分别DP。
		  首先要知道，在我们还没毁掉一条边的时候，敌人补任意一条边就会存在一个环，而上述的最小边肯定会包含在这个环里面。为什么？因为如果最小边不包含在这个环里，那最小边还是一个桥，那我们就毁掉这条最小边好了。
		  也就是说，敌人加的一条边肯定两端分别在我们新定义的两颗树里。这就是为什么要最小边的两个端点分别建树的原因了。
		  理解到这里就简单啦，对于新树A，我们在里面找一条以根为一端的链，使得链尽量包含该树中权值最小的边。两颗树两条链，就是敌人要补边连起来的链。但是直接找尽量包含树中权值最小的边比较麻烦，细心发现，既然是一条链，说明树中任何节点的两个不同分支不可能同时存在在链里面。这样，我们又把问题转化为“求所有节点的次小边权的最小值，并且最小边权和次小边权不在同一分支”....有点乱，就是“次小分支”啦。

	http://www.cnblogs.com/wuyiqi/archive/2011/11/04/2235671.html
	http://www.gonglin91.com/category/acm/dp/treedp/

	收获：一开始用树DP找节点的次小边权的最小值，用f[u].fir/f[u].sec来表示最小/次小分支边权，但是这样是求树的最小/次小值，有可能最小/次小在同一分支，所以跪了...
		  之后成了现在这样，f[u]表示以u为根的子树的最小边权。但是在维护f[u]的时候要同时更新ans，这是考细节的=_=||，无数WA之后自己出了个数据才找到WA点。    
		  简单记一下dfs的修改过程：
		  		dfs( Node u ) {
					for every child edge(u,v,w) do {
						dfs(v)
						Min = min(w, f[v])				;当前边E(u,v,w)应该算跟v同一个分支。  我一开始是w更新一次，f[v]更新一次，果断跪
						if f[u] >= Min then {
							ans = min(ans, f[u])		;旧最小分支充当次小分支，然后更新u的dp值
							f[u] = Min
						} else {
							ans = min(ans, Min)			;当前是新分支，就算f[u]<Min，也有可能该分支Min就是我们要找的次小分支
						}
				}
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN		10005
#define		MAXM		100005
#define		INF			999999999
struct Edge {
	int u, v, w, next;
} edge[MAXM * 2], e[MAXM];
int head[MAXN], dfn[MAXN], low[MAXN], S[MAXN], belong[MAXN], f[MAXN];
bool in_stack[MAXN], vis[MAXM * 2];
int n, edge_num, S_top, Order, Index, ans;
void init()
{
	edge_num = Order = S_top = 0;
	Index = 1;
	memset(head, -1, sizeof(head));
	memset(dfn,   0, sizeof(dfn));
	memset(vis, false, sizeof(vis));
	memset(in_stack, false, sizeof(in_stack));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
	S[S_top++] = u;
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) if(!vis[k])  {
		vis[k] = vis[k^1] = true;
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
void dfs(int u, int father)
{
	f[u] = INF;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v, w = edge[k].w;
		if(v == father) continue;
		dfs(v, u);
		w = min(w, f[v]);
		if(f[u] >= w) {
			ans = min(ans, f[u]);
			f[u] = w;
		} else ans = min(ans, w);
	}
}
int main()
{
	int u, v, w, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
			e[i].u = u, e[i].v = v, e[i].w = w;
		}
		Tarjan(1);
		//for(int i = 1; i <= n; i++) printf("belong[%d] = %d\n", i, belong[i]);
		if(Order == 1) {
			printf("-1\n");
			continue;
		}
		edge_num = 0;
		memset(head, -1, sizeof(head));
		Edge Min_Edge;
		Min_Edge.w = INF;
		for(int i = 0; i < m; i++) {
			u = belong[e[i].u], v = belong[e[i].v];
			if(e[i].u > n || e[i].v > n || u == v) continue;
			add_edge(u, v, e[i].w), add_edge(v, u, e[i].w);
			if(Min_Edge.w > e[i].w) Min_Edge.w = e[i].w, Min_Edge.u = u, Min_Edge.v = v;
		}
		ans = INF;
		dfs(Min_Edge.u, Min_Edge.v);
		dfs(Min_Edge.v, Min_Edge.u);
		if(ans == INF) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}

/*
	题意: 在一棵树上，有一些边是幸运边，现要求出点组(i, j, k)的数量，使得i 到j 的路径上和i 到k 的路径上都至少有一条幸运边。

	分析: lucky_pair = all - unlucky_pair
		  将点按非幸运便缩联通块X. Y = n - X, 则从点集X内随意取两个点, 再从Y集内取一个点, 这三个点构成unlucky_pair, 一共有
  		  P(|X|, 2) * |Y| 个unlucky_pair ;
		  另外还有从X里随意取三个点, 构成unlucky_pair, 共有P(|X|, 3)个

*/
#include <stdio.h>
#include <string.h>
#define		MAXN		100005
typedef		long long 		ll;
struct Edge {
	int u, v, next;
	bool islucky;
} edge[MAXN*2];
int n, edge_num, head[MAXN];
bool vis[MAXN*2];

bool islucky(int x)
{
	while(x) {
		if(x % 10 != 4 && x % 10 != 7) return false;
		x /= 10;
	}
	return true;
}
void add_edge(int u, int v, bool islucky)
{
	edge[edge_num].u = u, edge[edge_num].v = v; 
	edge[edge_num].next = head[u]; edge[edge_num].islucky = islucky;
	head[u] = edge_num++;
}
void init()
{
	memset(head, -1, sizeof head);
}
int  dfs(int u)
{
	int many = 1;
	for(int k = head[u]; k != -1; k = edge[k].next) if(!vis[k] && !edge[k].islucky) {
		vis[k] = vis[k^1] = true;	
		int v = edge[k].v;
		many += dfs(v);
	}
	return many;
}
int main()
{
	scanf("%d", &n);
	init();
	for(int i = 0; i < n-1; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u, v, islucky(w)), add_edge(v, u, islucky(w));
	}
	
	ll ans = (ll)n * (ll)(n-1) * (ll)(n-2);
	for(int i = 0; i < edge_num; i += 2) if(!vis[i] && !edge[i].islucky) {
		ll many = dfs(edge[i].u);
		ans -= many * (many-1) * (n - many) * 2 + many * (many - 1) * (many - 2);
	}
	printf("%I64d\n", ans);
	return 0;
}

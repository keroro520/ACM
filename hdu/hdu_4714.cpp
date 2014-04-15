/*
	树构造  好题
	题意：给一颗树，每剪掉一条边或者连上一条边都付出代价1.问把树变成环最少需要代价。

	http://blog.csdn.net/dongdongzhang_/article/details/11395305
	http://www.cnblogs.com/kiwi-bird/p/3310970.html
*/
#pragma comment(linker, "/STACK:102400000,102400000")

#include <stdio.h>
#include <string.h>
#define		MAXN		1000005
int head[MAXN];
struct Edge {
	int v, next;
} edge[MAXN * 2];
int n, edge_num, ans;
void init()
{	
	edge_num = 0;
	memset(head,  -1, sizeof(head));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}

int  dfs(int u, int father)			//返回是否还是u的子节点
{
	int chains = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		chains += dfs(v, u);
	}
	if(chains < 2) return 1;
	else {
		if(u == 1) ans += chains - 2;
		else ans += chains - 1;
		return 0;
	}
}
int main()
{
	int cases, u, v;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		ans = 0;
		dfs(1, 1);
		printf("%d\n", ans * 2 + 1);
	}
	return 0;
}

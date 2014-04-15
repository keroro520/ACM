/*
	欧拉回路   经典题
	题意：每条边经过刚好两次，最后回到起点，输出路线

	思路：dfs  
*/
//poj 2230
#include <string.h>
#include <stdio.h>
#define		MAXN		10005
#define		MAXM		50005*2
struct Edge {
	int v, next;
} edge[MAXM];
int n, edge_num, head[MAXN];
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void dfs(int u)
{
	while(head[u] != -1) {
		int k = head[u];
		int v = edge[k].v;
		head[u] = edge[k].next;
		dfs(v);
	}
	printf("%d\n", u);			//TODO  不解，放在后面就对，放在前面就WA。。
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
int main()
{
	int m, u, v;
	while(scanf("%d%d", &n, &m) != EOF) {
		init();
		while(m--) {
			scanf("%d%d", &u, &v);
			add_edge(u, v), add_edge(v, u);
		}
		dfs(1);
	}
	return 0;
}

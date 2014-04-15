/*
	二分图 最小路径覆盖

	题意：给n个立方体，大的可以套住小的，但是一个大的只能套住一个小的（但是小的里面可以再套，即可以嵌套不可并行）。问最少可以剩下几个立方体

	思路：a可以套住b，就连边a->b，那么就能形成一个DAG，问题转化为要覆盖图中所有点，最少需要多少条边。即最小路径覆盖


	跟hdu_3861很像。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN 	505
struct Edge {
	int v, next;
} edge[MAXN * MAXN];
int head[MAXN], a[MAXN][3], link[2*MAXN], vis[2*MAXN];
int n, edge_num, when;

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(vis, 0, sizeof(vis));
	when = 0;
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool judge(int x, int y)
{
	for(int i = 0; i < 3; i++) if(a[x][i] >= a[y][i]) return false;
	return true;
}
bool find(int u)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(vis[v] == when) continue;
		vis[v] = when;
		if(link[v] == -1 || find(link[v])) {
			link[v] = u;
			return true;
		}
	}
	return false;
}
int  max_match()
{
	int ans = 0;
	memset(link, -1, sizeof(link));
	for(int i = 0; i < n; i++) {
		when++;
		ans += find(i);
	}
	return ans ;
}
int main()
{
	while(scanf("%d", &n) != EOF && n) {
		init();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 3; j++) scanf("%d", &a[i][j]);
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)  if(i != j && judge(i, j)) {
				add_edge(i, j);
		}
		printf("%d\n", n - max_match());
	}
	return 0;
}

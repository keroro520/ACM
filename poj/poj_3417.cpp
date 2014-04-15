/*
	树形DP   LCA  统计  好题  神题

	题意：在一个无向树上给出若干条sample paths，最后输出每条边被多少条sample paths覆盖。

	思路：暴力法是LCA直接暴搞，TLE。
		  然后想到像一维线段树那样标记法add[]搞，于是对于每条sample path(u,v)，标记add[u]++, add[v]++, add[ ancester(u,v) ] -= 2
		  但是后面就不知道怎么像一维线段树那样统计了。想了很久都没办法。然后看题解。
		  哇靠，太巧妙了！dfs回溯统计add，太妙了！！！赞！

			//最后对整个图搜一遍，回溯的时候每个边加一下儿子几点add[]的值就可以了。
			int dfs(int u, int fa)
			{
				for(int k = head[u]; k != -1; k = edge[k].next) {
					int v = edge[k].v;
					if(v == fa) continue;
					times[ k/2+1 ] = dfs(v, u);			//k/2+1是对应的边 
					add[u] += add[v];
				}
				return add[u];
			}

*/
//codeforce round 121 E     problem/191/C
//poj 3417  更隐式的提法

#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN		100005
#define		ANC_SIZE	30			//原本定为34，找了好久才发现错误，会导致LCA错误
int head[MAXN], depth[MAXN], up[MAXN], times[MAXN], add[MAXN], ancester[MAXN][ANC_SIZE];
bool leaf[MAXN];
struct Edge { 
	int v, next;
} edge[MAXN * 2];
int n, edge_num;
void add_edge(int u, int v)
{
	edge[edge_num].v = v;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(times, 0, sizeof(times));
	memset(add,   0, sizeof(add));
	memset(leaf, false, sizeof(leaf));
}
void build(int u, int fa, int d)
{
	depth[u] = d;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		ancester[v][0] = u;			//LCA的初始化ancester[x][0] = father[x]
		up[v] = k^1;
		build(v, u, d+1);
	}
	if( edge[ head[u] ].next == -1) leaf[u] = true;
}
int Find_Anc(int u, int v)
{
	if(depth[u] < depth[v]) swap(u, v);
	int k = depth[u] - depth[v];
	for(int i = 0; i < ANC_SIZE; i++)
		if(k & (1 << i)) u = ancester[u][i];
	if(u == v) return v;
	for(int i = ANC_SIZE - 1; i >= 0; i--) 
		if(ancester[u][i] != ancester[v][i]) {
			u = ancester[u][i], v = ancester[v][i];
		}
	return ancester[u][0];
}
void calc(int u, int v)
{
	add[Find_Anc(u, v)] -= 2;
	add[u]++, add[v]++;
}
void Anc_init()
{
	for(int j = 1; j < ANC_SIZE; j++)
		for(int i = 1; i <= n; i++)
			ancester[i][j] = ancester[ ancester[i][j-1] ][j-1];
}
//void solve(int u)			//这是我之前统计的办法，是错的。
//{
//	int sum = add[u];
//	while(u != 1) {
//		times[ up[u]/2 + 1] += sum;
//		u = edge[ up[u] ].v;
//		sum += add[u];
//	}
//}
int dfs(int u, int fa)			//超妙的dfs！！！
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == fa) continue;
		times[ k/2+1 ] = dfs(v, u);
		add[u] += add[v];
	}
	return add[u];
}
int main()
{
	int u, v, query;
	scanf("%d", &n);
	init();
	for(int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v), add_edge(v, u);
	}
	up[1] = -1; 
	build(1, 0, 0);
	Anc_init();
	scanf("%d", &query);
	while(query--) {
		scanf("%d%d", &u, &v);
		calc(u, v);
	}
	dfs(1, 0);
	for(int i = 1; i < n; i++) printf("%d ", times[i]);
	printf("\n");
	return 0;
}

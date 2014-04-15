/*
	树形DP 
	题意：一棵有权树，从根结点中放入K个机器人，求用这K个机器人遍历所有的结点最少的权值和 
	http://blog.csdn.net/ahero_happy/article/details/6747116
	http://www.cnblogs.com/kuangbin/archive/2012/08/29/2661928.html
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
#define		MAXK		12
struct Edge {
	int v, next,w;
} edge[MAXN * 2];
int n, Robot, edge_num;
int head[MAXN];
long long dp[MAXN][MAXK];
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v;
	edge[edge_num].w = w;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void DP(int u, int father)
{
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == father) continue;
		DP(v, u);
		for(int i = Robot; i >= 0; i--) {
			dp[u][i] += dp[v][0] + edge[k].w * 2;
			for(int j = 1; j <= i; j++)
				dp[u][i] = min(dp[u][i], dp[u][i-j] + dp[v][j] + j*edge[k].w);
		}
	}
}

int main()
{
	int S, u, v, w;
	while(scanf("%d%d%d", &n, &S, &Robot) != EOF) {
		init();
		for(int i = 1; i < n; i++) {
			scanf("%d%d%d", &u, &v, &w);
			add_edge(u, v, w);
			add_edge(v, u, w);
		}
		memset(dp, 0, sizeof(dp));
		DP(S, -1);
		printf("%I64d\n", dp[S][Robot]);
	}
	return 0;
}

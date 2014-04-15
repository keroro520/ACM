/*
	差分约束  图论  好题   经典题
	题意：n个军营排成一排，已知{Ci}表示军营i最多有ci个士兵。若干估计(i,j,k)，表军营i到军营j一共‘至少’有k个士兵。
		  判断估计是否正确，不正确输出"Bad Estimations"，否则输出可能的最少总士兵数。

	思路：构图还是想了很久的。挺经典的构图
		
		  没有想到还必须得建(0->i, 0)!!!  不过我想SPFA一开始把所有点push到栈里面也是可以的。

		  求最小值，用最长路

			si - si-1 <= ci
			si-1 >= si - ci

			si - sj-1 >= x
			si >= sj-1 + x
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		1005
#define		MAXM		((10000 + 1005)*2)
struct Edge {
	int v, next, w;
} edge[MAXM];
int  head[MAXN], times[MAXN], S[MAXN], dis[MAXN];
bool inq[MAXN] ;
int  n, m, edge_num;
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool SPFA(int s)
{
	int top = 0;
	memset(dis, 128, sizeof(dis));
	memset(times, 0, sizeof(times));
	memset(inq, false, sizeof(inq));
	dis[s] = 0;
	S[top++] = s;
	while(top) {
		int u = S[--top];
		inq[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v , w = edge[k].w;
			if(dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if(!inq[v]) {
					inq[v] = true, S[top++] = v;
					if(++times[v] > n) return false;
				}
			}
		}
	}
	return true;
}
int main()
{
	while(scanf("%d %d", &n, &m) != EOF) {
		init();
		int x, sum = 0, u, v, w;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &x);
			sum += x;
			add_edge(i, i-1, -x);
			add_edge(i, 0, -sum);
			add_edge(0, i, 0   );		// Attention
		}
		while(m--) {
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u-1, v, w);
		}
		if(!SPFA(0)) puts("Bad Estimations");  else printf("%d\n", dis[n]);
	}
	return 0;
}

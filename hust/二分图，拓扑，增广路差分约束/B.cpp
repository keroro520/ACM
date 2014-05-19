/*
	差分约束  图论  好题   经典题
	题意：n个军营排成一排，已知{Ci}表示军营i最多有ci个士兵。若干估计(i,j,k)，表军营i到军营j一共‘至少’有k个士兵。
		  判断估计是否正确，不正确输出"Bad Estimations"，否则输出可能的最少总士兵数。

	思路：构图还是想了很久的。挺经典的构图
		
		  没有想到还必须得建(0->i, 0)!!!  不过我想SPFA一开始把所有点push到栈里面也是可以的。
		  是否创建起始点的区别就是, 对于任意点i, 边(s,i,_)有没有约束条件, 有的话就把括号里面的'_'替换成约束条件.

		  求最小值，用最长路

			si - si-1 <= ci
			si-1 >= si - ci

			si - sj-1 >= x
			si >= sj-1 + x
*/

// edge(u,v,w)		=> 		the correct value of edge from u to v is not less then w

#include <stdio.h>
#include <string.h>
#define			MAXN		1005
#define			MAXM		10005
struct Edge {
	int v, next, w;
} edge[MAXM + MAXN*2];
int edge_num, n, m;
int head[MAXN], dis[MAXN], times[MAXN], S[MAXN];
bool ins[MAXN];

void init()
{
	edge_num = 0 ;
	memset(head, -1, sizeof head);
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w;
	edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool SPFA(int s)
{
	int top = 0;
	memset(times,0 , sizeof times);
	memset(dis, 128, sizeof dis);
	memset(ins, 0  , sizeof ins);
	S[top = 0, top++] = s;
	dis[s] = 0;
	while (top) {
		int u = S[--top];
		ins[u] = false;
		for (int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v, w = edge[k].w;
			if (dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!ins[v]) {
					if (++times[v] > n) return false;
					ins[v] = true, S[top++] = v;
				}
			}
		}
	}
	return true;
}
int main()
{
	int c, u, v;
	while(scanf("%d %d", &n, &m) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &c), add_edge(i,i-1,-c);
		while(m--) {
			scanf("%d %d %d", &u, &v, &c);
			add_edge(u-1,v,c);
		}
		for(int i = 1; i <= n; i++) add_edge(0, i, 0);
		if (SPFA(0)) printf("%d\n", dis[n]);
		else puts("Bad Estimations");
	}
	return 0;
}


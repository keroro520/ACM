
/*
	差分约束  好题  隐含条件
	题意：给出n个闭区间[ai,bi]，每个区间对应一个ci，表示集合Z在区间[ai,bi]内ci个相同元素，问集合Z至少有几个元素

	思路：就说说隐含条件吧，0 <= ai - ai-1 <= 1 ，我只想到 要小于等于1，没有想到要大于等于0，就WA了，这个点得记住，不然没办法当场思考出来.

		  由输入建边简单，难的是要发觉隐含条件，就是这是个`数列区间`，有0 <= s[i+1] - s[i] <= 1(s[i]表[0,i]有多少个Z元素)这个隐含条件...

			an - a0 >= 0
			an >= a0 + 0
			
			av - au-1 >= k
			av >= au-1 + k
			
			ai - ai-1 <= 1
			ai-1 >= ai - 1
			
			ai - ai-1 <= 0
			ai-1 >= ai + 0
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define			MAXN		50005
struct Edge {
	int v, next, w;
} edge[MAXN * 4];
int  head[MAXN], S[MAXN], dis[MAXN];
bool ins[MAXN];
int  n , edge_num;
void init()
{
	edge_num = n = 0;
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void SPFA(int s)
{
	memset(dis, 128,   sizeof(dis));  
	memset(ins, false, sizeof(ins));
	int top = 0;
	dis[s] = 0;
	S[top++] = s;
	while(top) {
		int u = S[--top];
		ins[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v, w = edge[k].w;
			if(dis[v] < dis[u] + w) {
				dis[v] = dis[u] + w;
				if(!ins[v]) {
					ins[v] = true, S[top++] = v;
				}
			}
		}
	}
}
int main()
{
	int m, u, v, w;
	while(scanf("%d", &m) != EOF) {
		init();  
		n = 0;
		while(m--) {
			scanf("%d %d %d", &u, &v, &w);
			n = max(n,  v);
			add_edge(u-1, v, w);
		}
		for(int i = 1; i <= n; i++) add_edge(i, i-1, -1), add_edge(i-1, i, 0);
		SPFA(0);
		printf("%d\n", dis[n]);
	}
	return 0;
}

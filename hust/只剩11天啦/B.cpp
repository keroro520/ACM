// WA
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN 100005
struct Edge {
	int v, next, w;
} edge[MAXN * 2];
int head[MAXN];
int n, edge_num;

void add_edge(int u, int v, int w)
{
	edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof head);
}
int  calc(int u)
{
	int sum = 0, Max = 0;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		sum += edge[k].w;
		Max = max(Max, edge[k].w);
	}
	return Max > (sum+1)/2 ? Max : (sum+1)/2;
}
int main()
{
	int Cas = 0, cases, u, v, w;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		init();
		int ans = 0, sum = 0;
		for(int i = 1; i < n; i++) {
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
			sum += w;
		}
		for(int i = 1; i <= n; i++) ans += calc(i);
		ans -= sum;
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}

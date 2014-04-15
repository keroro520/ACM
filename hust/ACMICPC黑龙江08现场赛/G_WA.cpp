//还是WA 可是感觉再能力范围内，纠结
//http://acm.hdu.edu.cn/showproblem.php?pid=2452
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN 	10005
struct Edge {
	int v, next;
} edge[MAXN * MAXN / 2];
int head[MAXN], val[MAXN], dp[MAXN][2], Q[MAXN], in[MAXN];
int n, edge_num, INF = 999999999;

void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	memset(in, 0, sizeof(in));
	memset(head, -1, sizeof(head));
	edge_num = 0;
}
void Update(int u, int v)
{
	if(dp[u][1] != -INF)     dp[v][0] = max(dp[u][1] + val[v], dp[v][0]);//, printf("# %d  %d\n", u, v);
	if(dp[u][0] != -INF) {
		if(dp[v][1] != -INF) dp[v][1] = min(dp[u][0] + val[v], dp[v][1]);//, printf("$ %d  %d\n", u ,v);
		else 				 dp[v][1] = dp[u][0] + val[v];
	}
}
int  solve(int s)
{
	int car = 0, cdr = 0, ans = -1;
	for(int i = 1; i <= n; i++) dp[i][0] = -INF, dp[i][1] = -INF;
	//dp[s][0] = val[s];  //dp[s][1] = 0;
	dp[s][1] = val[s];
	Q[car++] = s;
	while(cdr < car) {
		int u = Q[cdr++] ;
		if(head[u] == -1) ans = max(ans, max(dp[u][0], dp[u][1]));
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			Update(u, v);
			if(--in[v] == 0) Q[car++] = v;
		}
	}
	return ans;
}
int main()
{
	//memset(&INF, 127, sizeof(INF));
	int F, m, u, v;
	while(scanf("%d %d %d", &n, &m, &F) != EOF) {
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &val[i]);
		while(m--) {
			scanf("%d %d", &u, &v);
			add_edge(u, v);
			in[v] ++;
		}
		int st = -1;
		for(int i = 1; i <= n; i++) if(!in[i]) { st = i; break; }
		if(n == 1) puts(val[n] >= F    ? "Victory" : "Glory");
		else 	   puts(solve(st) >= F ? "Victory" : "Glory");
	}
	return 0;
}

/*
	图DP  记忆化搜索  好题
	题意：有向点权图，从点1出发目的地点n，每步从u走到v，路径权值x变为lcm(x,p[v])，但必须满足lcm(x,p[v]) != x才能走，也就是每一步lcm都必须得有边变化。问有多少条路径可以从1到达点n，且路径权值（也就是最后的lcm）为K.

	思路：一开始想拓扑序DP，死活解决不了环的情况，看爱神用记忆化搜索来做...唉，还是没理解什么时候用拓扑DP什么时候用记忆化搜索。

		  再好好体会一下拓扑DP与记忆化搜索的区别！
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#define		MAXN		2005
#define		MAXFACT		2005
#define		MOD			1000000007
typedef	long long		ll;
struct Edge {
	int v, next;
} edge[20005];
int K, n, edge_num, idx;
int head[MAXN], pos[1000005], fact[MAXFACT], lcm[MAXFACT][MAXFACT], p[MAXN];
ll f[MAXN][MAXFACT];

int  GCD(int x, int y)
{
	return y == 0 ? x : GCD(y, x % y);
}
int  LCM(int x, int y)
{
	return x / GCD(x,y) * y;
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	idx = edge_num = 0;
	memset(lcm,  -1, sizeof  lcm);
	memset(head, -1, sizeof head);
	memset(pos,  -1, sizeof  pos);
	memset(f,    -1, sizeof    f);
	for(int i = 1, oo = (int)sqrt(K*1.0+0.5); i <= oo; i++) 
		if(K % i == 0) {
			fact[idx] = i, pos[i] = idx++;
			if(K / i != i) fact[idx] = K / i, pos[K/i] = idx++;
		}
	for(int i = 0; i < idx; i++) for(int j = 0; j < idx; j++) lcm[i][j] = pos[LCM(fact[i], fact[j])];
}

ll   dfs(int u, int x)
{
	if(f[u][x] != -1) return f[u][x];
	if(u == n) return x == K;
	ll & sum = f[u][x];
	sum = 0;

	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(pos[p[v]] == -1) continue;
		int _lcm = lcm[x][pos[p[v]]];
		if(_lcm == x) continue;
		dfs(v, _lcm);
		sum += f[v][_lcm];
		sum %= MOD;
	}
	return sum;
}
ll   solve()
{
	if(pos[p[1]] == -1) return 0;
	f[n][pos[K]] = 1;
	ll  ans = dfs(1, pos[p[1]]);
	return ans;
}
int main()
{
	int m, u, v;
	while(scanf("%d %d %d", &n, &m, &K) != EOF) {
		init();
		while(m--) {
			scanf("%d %d", &u, &v);
			add_edge(u, v);		//用逆向边不知到怎么由lcm,x推出y,,
		}
		for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
		ll  ans = solve();
		printf("%d\n", (int)ans);
	}
	return 0;
}

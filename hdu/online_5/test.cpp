#include <math.h>
#include <stdio.h>
#include <string.h>
#define		MAXN		205
struct People {
	int sx, sy, tx, ty;
} a[MAXN];
struct Edge {
	int v, next;
	double w;
} edge[MAXN*MAXN];
int head[MAXN], path[MAXN], ans_path[MAXN];
bool vis[MAXN];
double dis[MAXN][MAXN];
double ans;
int n, edge_num;
inline		int		hash(int x) { return n + x; }
void dfs(int u, int sum, double tot)
{
	if(tot >= ans) return ;
	if(u <= n && !vis[hash(u)]) return ;		//i+还没到达就到i-
	if(sum == 2*n) {
		ans = tot;
		for(int i = 1; i <= sum; i++) ans_path[i] = path[i];// printf("! %d\n", path[i]);
		return ;
	}
	for(int k = head[u]; k != -1; k = edge[k].next ) {
		int v = edge[k].v;
		if(vis[v]) continue;
		vis[v] = true;
		path[sum+1] = v;
		dfs(v, sum+1, tot+edge[k].w);
		vis[v] = false;
	}
}
inline double SQR(double x) { return x * x; }
double calc(int x1, int y1, int x2, int y2)
{
	return sqrt(SQR((x1-x2)*1.0) + SQR((y1-y2)*1.0));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = dis[u][v];
	head[u] = edge_num++;
}
void build(int n)
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++) {		//i+ -> k-
		for(int k = 1; k <= i; k++)
			add_edge(hash(i), k);
	}
	for(int i = 1; i < n; i++) {		//(i+1)+  ->  i+
		add_edge(hash(i+1), hash(i));
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			add_edge(i, hash(j));
		}
	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++) {
			add_edge(i, j);
		}
}

int main()
{
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d%d%d%d", &a[i].sx, &a[i].sy, &a[i].tx, &a[i].ty);
		for(int i = 1; i <= n; i++) 
			for(int j = 1;  j <= n; j++) {
				dis[j][i] = dis[i][j] = calc(a[i].tx, a[i].ty, a[j].tx, a[j].ty);	//i- -> j-
				dis[i][hash(j)] = dis[hash(j)][i] = calc(a[i].tx, a[i].ty, a[j].sx, a[j].sy);	//i- -> j-
				dis[hash(i)][j] = dis[j][hash(i)] = calc(a[i].sx, a[i].sx, a[j].tx, a[j].ty);
				dis[hash(i)][hash(j)] = dis[hash(j)][hash(i)] = calc(a[i].sx, a[i].sy, a[j].sx, a[j].sy);
			}
		build(n);
		ans = 999999999999;
		for(int i = n+1; i <= 2*n; i++) {
			memset(vis, false, sizeof(vis));
			path[1] = i;
			vis[i] = true;
			dfs(i, 1, 0);
		}
		for(int i = 1; i <= 2*n; i++) {
			if(ans_path[i] <= n) printf("%d-", ans_path[i]);
			else printf("%d+", ans_path[i] - n);
			if(i == 2*n) puts(""); else printf(" ");
		}
	}
	return 0;
}

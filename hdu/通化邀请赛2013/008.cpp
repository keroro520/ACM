#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		N	22
#define		INF	999999999
int f[N][N][N][N], a[N], b[N], sum[2][N];
bool vis[N][N][N][N];
int n;
inline int Sum(int i, int j, int k, int h)
{
	return sum[0][j] - sum[0][i-1] + sum[1][h] - sum[1][k-1];
}
int dfs(int i, int j, int k , int h)
{
	if(i > j || k > h) return 0;
	int &x = f[i][j][k][h];
	if(vis[i][j][k][h]) return x;
	vis[i][j][k][h] = true;
	//if(i == j && k == h) return x = max(a[i] - b[k], b[k] - a[i]);
	
	x = -INF;
	//if(i != j) 
		x = max(x, max(-dfs(i, j-1, k, h) + a[j], -dfs(i+1, j, k, h) + a[i]));
	//if(h != k) 
		x = max(x, max(-dfs(i, j, k, h-1) + b[h], -dfs(i, j, k+1, h) + b[k]));
	printf("# (%d %d %d %d) %d\n", i,j,k,h,x);
	return x;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[0][i] = sum[0][i-1] + a[i];
		for(int i = 1; i <= n; i++) scanf("%d", &b[i]), sum[1][i] = sum[1][i-1] + b[i];
		//memset(f, 128, sizeof(f));
		memset(vis, false, sizeof(vis));
		int res = dfs(0, n+1, 0, n+1);
		//int res = dfs(1, n, 1, n);
		printf("%d\n", res);
	}
	return 0;
}

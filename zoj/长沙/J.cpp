#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN	(125)
double p[MAXN][MAXN];
double f[10005][MAXN];
int    a[10005];
int M, n;
inline	int	 C(int n, int m)
{
	return n*(n-1)/2*(n-2)/3;
}
int main()
{
	while(scanf("%d", &M) != EOF) {
		int R = C(M,3);
		for(int i = 1; i <= R; i++) for(int j = 1; j <= R; j++) scanf("%lf", &p[i][j]);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i]++;
	
		memset(f, 0, sizeof(f));
		for(int i = 1; i <= R; i++) f[0][i] = 1;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= R; j++) {
				f[i][j] = f[i-1][j] * p[j][a[i]];
				if(a[i] == j) {
					for(int k = 1; k <= R; k++)
						f[i][j] = max(f[i][j], f[i-1][k] * p[k][j]);
				}
			}
		double ans = 0;
		for(int i = 1; i <= R; i++) ans = max(ans, f[n][i]);
		printf("%.6f\n", ans);
	}
	return 0;
}
//f[i][j] 第i关，当前队伍为j
//f[i][j] = f[i-1][j] * p[j][a[i]]	
//		  = f[i-1][k] * p[k][j] , a[i] == j

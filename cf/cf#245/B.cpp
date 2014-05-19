#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		1005
int n, m, a[MAXN][MAXN], f[6][MAXN][MAXN];
int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for( int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) f[1][i][j] = max(f[1][i-1][j], f[1][i][j-1]) + a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--) f[2][i][j] = max(f[2][i-1][j], f[2][i][j+1]) + a[i][j];
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= m; j++) f[3][i][j] = max(f[3][i+1][j], f[3][i][j-1]) + a[i][j];
	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--) f[4][i][j] = max(f[4][i+1][j], f[4][i][j+1]) + a[i][j];

	int ans = 0;
	for (int i = 2; i < n; i++)		//最后时刻找到了这个hack点
		for (int j = 2; j < m; j++) {
			int a1 = f[1][i][j-1] ;
			int a2 = f[4][i][j+1] ;
			int a3 = f[2][i-1][j] ;
			int a4 = f[3][i+1][j] ;
			ans = max(ans, a1+a2+a3+a4);

			a1 = f[3][i][j-1] ;
			a2 = f[2][i][j+1] ;
			a3 = f[1][i-1][j] ;
			a4 = f[4][i+1][j] ;
			ans = max(ans, a1+a2+a3+a4);
		}
	
	printf("%d\n", ans);
	return 0;
}

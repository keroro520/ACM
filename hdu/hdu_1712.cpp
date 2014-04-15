/*
	分组背包模板题
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[105][105], f[105*105], n, m;

int main()
{
	while(scanf("%d%d", &n, &m) , n || m) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
		memset(f, 128, sizeof(f));
		f[0] = 0;
		for(int i = 1; i <= n; i++)
			for(int j = m; j >= 1; j--)		//逆向
				for(int k = 1; k <= j; k++)
					f[j] = max(f[j], f[j-k]+a[i][k]);
		int ans = 0;
		for(int i = 1; i <= m; i++) ans = max(ans, f[i]);
		printf("%d\n", ans);
	}
	return 0;
}

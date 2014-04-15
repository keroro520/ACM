/*
	实现成另外一道题了。。。实现的题目：一个数字环，取一段，使得该段总和 模K 为0，求方案数。。。

	记做一道题？
*/
#include <stdio.h>
#include <string.h>
#define			MAXN			50005
#define			MAXK			205
int n, K, a[MAXN], dp[MAXN][MAXK], cnt[MAXK];

int main()
{
	while(scanf("%d %d", &n, &K) != EOF) {
		
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		
		memset(dp, 0, sizeof dp);
		for(int i = 1; i <= n; i++) {
			dp[i][a[i]%K]++;
			for(int j = 0; j < K; j++) dp[i][j] += dp[i-1][((j-a[i])%K+K)%K];
		}
		int ans = 0;
		for(int i = 1; i <= n; i++) ans += dp[i][0];

		memset(cnt, 0, sizeof cnt);
		int tmp = a[1];
		for(int i = n; i > 2; i--) {
			tmp += a[i];
			cnt[tmp % K]++;
		}
		ans += cnt[0];
		for(int i = 3; i < n; i++) {
			cnt[tmp%K]--;
			tmp -= a[i];
			tmp += a[i-1];
			ans += cnt[0];
		}
		printf("%d\n", ans);
	}
	return 0;
}

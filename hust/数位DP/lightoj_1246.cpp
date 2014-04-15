/*
	数位统计  DP  推公式   组合数	 好题	递推  染色  再加一个好题
	思路：这些公式我哪会呀...不错啦...
*/
#include <stdio.h>
#include <string.h>
#define		MOD		(1000000007LL)
long long dp[400][400], C[400][400];


void init()
{
	for(int i = 1; i <= 391; i++) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
	}
	for(int i = 1; i <= 391; i++) {
		dp[1][i] = 1;
		for(int j = 2; j <= 50; j++) {
			dp[j][i] = (dp[j][i-1]*j + dp[j-1][i-1]*j) % MOD;
		}
	}
	/*
	dp[1][1] = 1;
	for(int i = 2; i <= 50; i++)
		for(int j = 2; j <= 361; j++)
			dp[i][j] = (dp[i-1][j]*i%MOD + dp[i-1][j-1]*i%MOD) % MOD;
	*/
}
int main()
{
	int Cas = 0, cases, m, n, k;
	init();	
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d%d", &m, &n, &k);
		if(n == m && n == 0) {
			printf("Case %d: %d\n", ++Cas, k);
			continue;
		}
		m++, n++;
		int x = m*n/2 + ((m & 1) && (n & 1));
		int y = m*n - x;
		long long ans = 0;
		for(int i = 1; i < k; i++)
			for(int j = 1; j + i <= k; j++)
				ans = (ans + (dp[i][x] * dp[j][y]) % MOD * C[k][i] % MOD * C[k-i][j] % MOD) % MOD;
				//ans += ((dp[i][x] + dp[k-i][y]) % MOD * (C[k][i] % MOD)) % MOD;
		printf("Case %d: %lld\n", ++Cas, ans);
	}
	return 0;
}
//dp[i][j] = dp[i-1][j]*i + dp[i-1][j-1]*i*j

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
		dp[1][i] = 1;
		for(int j = 2; j <= 50; j++) {
			dp[j][i] = (dp[j][i-1]*j + dp[j-1][i-1]*j) % MOD;
		}
	}
}
int main()
{
	int m, n, k;
	init();	
	scanf("%d%d%d", &m, &n, &k);
	long long ans = 0;
	for(int i = 1; i <= k; i++) 
		ans += dp[i][n*m];
	printf("%lld\n", ans);
	return 0;
}

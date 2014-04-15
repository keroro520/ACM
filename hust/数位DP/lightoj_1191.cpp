/*
	数位统计DP
	题意：将n分成k个不大于m的数的和有多少种方案，1,1,2与2,1,1是不同方案。

	思路：dp[n][k][m] = Σ(dp[n-i][k-1][m]) (1 <= i <= m)
		  预处理出所有dp值即可。
		  我原来还用数位DP的dfs搞...TLE惨了...
*/
//lightoj 1191
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;
#define		MAXN	52
long long dp[MAXN][MAXN][MAXN];
int n, m, k;

void initDP()
{
	for(int m = 1; m <= 50; m++) {
		for(int n = 1; n <= m;  n++) dp[n][1][m] = 1;

		for(int n = 1; n <= 50; n++)
			for(int k = 1; k <= 50; k++)
				for(int i = 1; i <= m && i <= n; i++)
					dp[n][k][m] += dp[n-i][k-1][m];
	}
}
int main()
{
	initDP();
	int cases, Cas = 0, n, m, k;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d%d", &n, &k, &m);		//n个码，k个单元，一个单元最多m个码
		printf("Case %d: %lld\n", ++Cas, dp[n][k][m]);
	}
	return 0;
}

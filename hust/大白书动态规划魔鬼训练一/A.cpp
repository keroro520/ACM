/*
	未测，oj挂了
	区间DP  回文串
	题意：给一个串，问最少划分数，使得每个划分都是回文串。这里的划分是连续的字串，如abcde有ab,cde划分，但abe不是划分。

	思路：区间DP搞出f[i][j]表[i,j]区间是否回文，然后dp一下算出最小划分数

		  一开始我是dfs算最小划分数，TLE
*/
#include <stdio.h>
#include <string.h>
using namespace std;
#define	MAXN	1005
int f[MAXN][MAXN], n, ans, dp[MAXN];
char s[1005];

int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%s", s);
		n = strlen(s);
		memset(f, 0, sizeof f);
		for(int i = 0; i < n; i++) f[i][i] = 1, f[i+1][i] = 1;
		for(int l = 0; l < n; l++)
			for(int i = n-1; i >= 0; i--) {
				int j = i + l;
				if(j >= n) continue;
				if(s[i] == s[j] && f[i+1][j-1]) f[i][j] = 1;
			}
		for(int i = 0; i < n; i++) {
			dp[i] = dp[i-1] + 1;
			for(int j = i-1; j >= 0; j--) if(f[j][i])
				dp[i] = min(dp[i], dp[j-1] + 1);
		}
		ans = dp[n-1];
		printf("%d\n", ans);
	}
	return 0;
}

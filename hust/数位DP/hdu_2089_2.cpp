/*
	数位DP
	记忆化搜索写一遍
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		1000005
#define		FIRST		(0)
int dp[30][3], digit[100];

int dfs(int pos, int have, bool up_limit)
{
	if(pos == -1) return have == 2;
	if(!up_limit && dp[pos][have] != -1) return dp[pos][have];

	int res = 0, nhave;
	int end = up_limit ? digit[pos] : 9;

	for(int i = FIRST; i <= end; i++) {
		if(i == 4 || have == 2) nhave = 2;
		else if(i == 6) nhave = 1;
		else if(have == 1 && i == 2) nhave = 2;
		else nhave = 0;

		res += dfs(pos-1, nhave, up_limit && (i == end));
	}
	if(!up_limit) dp[pos][have] = res;
	return res;
}
int calc(int x)
{
	memset(dp, -1, sizeof(dp));
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return dfs(pos-1, 0, 1);
}
int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF && n && m) {
		printf("%d\n", m - n + 1 - calc(m) + calc(n-1));
	}
	return 0;
}

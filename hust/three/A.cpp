/*
	数位DP 简单
*/
#include <stdio.h>
#include <string.h>

int dp[30], digit[30];
int dfs(int pos, bool full)
{
	if(pos == -1) return 1;
	if(!full && dp[pos] != -1) return dp[pos];
	int res = 0, end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) if(i != 3 && i != 8) {
		res += dfs(pos-1, full && i == end);
	}
	if(!full) dp[pos] = res;
	return res;
}
int calc(int x)
{
	int len = 0;
	while(x) {
		digit[len++] = x % 10;
		x /= 10;
	}
	return dfs(len-1, true);
}
int main()
{	
	int n;
	memset(dp, -1, sizeof(dp));
	while(scanf("%d", &n) , n) {
		printf("%d: %d\n", n, calc( n ) - 1);
	}
	return 0;
}

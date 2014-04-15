/*
	出题
	数位DP
	1-n的数中各个数位之和不超过p的数有多少？
*/
#include <stdio.h>
#include <string.h>
int dp[60][10000], digit[60];

int init(int x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
int dfs(int pos, int p, bool full)
{
	if(p < 0) return 0;
	if(pos == -1) return 1;
	if(!full && dp[pos][p] != -1) return dp[pos][p];

	int res = 0, end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++)
		res +=  dfs(pos-1, p-i, full && i == end);
	if(!full) dp[pos][p] = res;
	return res;
}
int calc(int n, int p)
{
	return dfs(init(n) - 1, p, true);
}
int main()
{
	int n, p;
	memset(dp, -1, sizeof(dp));
	scanf("%d%d", &n, &p);
	printf("%d\n", calc(n, p));
	return 0;
}

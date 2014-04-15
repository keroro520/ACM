/*
	数位DP简单题
*/
#include <stdio.h>
#include <string.h>
#define		FIRST		(0)
#define		MAXN		70
long long dp[MAXN][3];
int digit[MAXN];

int  init(long long n)
{
	int pos = 0;
	while(n) {
		digit[pos++] = n % 10;
		n /= 10;
	}
	return pos;
}
long long dfs(int pos, int have, int up_limit)
{
	if(pos == -1) return have == 2;
	if(!up_limit && dp[pos][have] != -1) return dp[pos][have];

	int nhave;
	int end = up_limit ? digit[pos] : 9;
	long long res = 0;

	for(int i = FIRST; i <= end; i++) {
		if(have == 2 || (have == 1 && i == 9)) nhave = 2;
		else if(i == 4) nhave = 1;
		else nhave = 0;
		res += dfs(pos-1, nhave, up_limit && (i == end));
	}
	if(!up_limit) dp[pos][have] = res;
	return res;
}
long long calc(long long n)
{
	memset(dp, -1, sizeof(dp));
	int Index = init(n);
	return dfs(Index-1, 0, true);
}
int main()
{
	int cases;
	long long n;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d", &n);
		printf("%I64d\n", calc(n));
	}
	return 0;
}

/*
	数位DP  有前导0处理
	题意：[l,r]中的数转为二进制后0的个数不小于1的个数的数。

	思路：常规数位DP，就是要注意前导 0
		  dp状态：dp[pos][one][zero]

		  注意点：
		  LL dfs(int pos, int one, int zero, bool full, bool first) {
		  	res += dfs(pos-1, one+i, zero+(i==0 && !first), full && i == end, first && i == 0);
			//zero表当前0的个数，那如果现在first为true的话zero即不应该增加！TODO
		  }
*/
//poj 3252
#include <stdio.h>
#include <string.h>
#define			MAXN		65
typedef				long long  LL ;
int digit[MAXN];
LL dp[MAXN][MAXN][MAXN];

int init(LL x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = (x & 1LL);
		x >>= 1LL;
	}
	return pos;
}
LL dfs(int pos, int one, int zero, bool full, bool first)
{
	if(pos == -1) {
		if(first) return 1;
		return zero >= one;
	}
	if(!first && !full && dp[pos][one][zero] != -1) return dp[pos][one][zero];

	LL res = 0;
	int end = full ? digit[pos] : 1;
	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, one+i, zero+(i==0 && !first), full && i == end, first && i == 0);	//TODO
	}
	if(!full && !first) dp[pos][one][zero] = res;
	return res;
}
LL calc(LL n)
{
	int Index = init(n);
	return dfs(Index-1, 0, 0, true, true) ;
}
int main()
{
	memset(dp, -1, sizeof(dp));
	LL l, r;
	while( scanf("%I64d%I64d", &l, &r) != EOF ) {
		printf("%I64d\n", calc(r) - calc(l-1));
	}
	return 0;
}

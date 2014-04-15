/*
	没过样例
	想用数位DP做，网上的没找到纯数位DP的方法。

	题意：求[l，r]有多少个0出现
*/
//poj 3286
#include <stdio.h>
#include <string.h>
#define		MAXPOS	33
typedef  	long long LL;
int digit[MAXPOS]; 
LL dp[MAXPOS];

int init(int x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
LL dfs(int pos, LL pre, bool full, bool first)
{
	if(pos == -1) return pre;
	if(!full && dp[pos] != -1) return dp[pos];

	int res = 0;
	int end = full ? digit[pos] : 9;

	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, pre + (i == 0 && !first), full && i == end, first && i == 0);
	}
	
	if(!full && !first) dp[pos] = res;
	return res;
}
LL calc(int n)
{
	memset(dp, -1, sizeof(dp));		//TODO
	return dfs(init(n)-1, 0, true, true);
}
int main()
{
	LL n, m;
	while(scanf("%lld%lld", &m, &n) != EOF && n != -1 && m !=  -1) 
		printf("(%lld   %lld)  %lld\n", calc(n), calc(m-1), calc(n) - calc(m-1));
	return 0;
}

/*
	数位DP
	题意：[l,r]内的平衡数
		  平衡数的定义：以某位为中心，两边力矩相等。
		  力矩定义：假设中心位为mid，则左力矩为sum{digit[i]*(mid-i)}, (i < mid)；右力矩同理。
	
	思路：枚举中心点，对每个中心点都搞一次数位DP。
		  dp[i][mid][preMoment] 表现在处理到i位，中心点在mid位，前i位的力矩和为preMoment。注意，实现里面把右力矩作为负数来算，让左右力矩抵消。

	//枚举中心位
	//for(int i = 0; i < Index; i++) ans += dfs(Index-1, i, 0, true);

	//状态转移
	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, central, sum + (pos-central)*i, up_limit && i == end);
	}
*/
#include <stdio.h>
#include <string.h>
#define	MAXN	20
int digit[MAXN];
long long dp[MAXN][MAXN][2005];
long long dfs(int pos, int central, int sum, bool up_limit)
{
	if(sum < 0) return 0;
	if(pos == -1) return sum == 0;
	if(!up_limit && dp[pos][central][sum] != -1) return dp[pos][central][sum];

	long long res = 0;
	int end = up_limit ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, central, sum + (pos-central)*i, up_limit && i == end);
	}
	if(!up_limit) dp[pos][central][sum] = res;
	return res;
}
int init(long long x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
long long calc(long long n)
{
	int Index = init(n);
	long long ans = 0;
	for(int i = 0; i < Index; i++) ans += dfs(Index-1, i, 0, true);

	return ans - Index + 1;		//TODO
}
int main()
{
	int cases;
	long long x, y;
	memset(dp, -1, sizeof(dp));
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d%I64d", &x, &y);
		printf("%I64d\n", calc(y) - calc(x-1));
	}	
	return 0;
}

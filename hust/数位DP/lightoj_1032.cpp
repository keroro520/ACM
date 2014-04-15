/*
	数位DP 简单题
	题意：设f(x)表示x的二进制有多少个1的右边还是1
		  12 = 1100B 有一个1的右边是1，所以f(12) = 1；f(15) = f(1111B) = 3；f(27) = f(11011B) = 2
		  计算[l,r]的所有f和.
	
	思路：模板题
		  dp[pos][x][sum]  前pos个数，最近（上一个）数的x，f值和为sum的DP值.
*/
//lightoj 1032
#include <stdio.h>
#include <string.h>
long long dp[33][2][33], digit[33];

int init(int x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = (x & 1);
		x >>= 1;
	}
	return pos;
}
long long dfs(int pos, int preNum, int sum, bool full)
{
	if(pos == -1) return sum;
	if(!full && dp[pos][preNum][sum] != -1) return dp[pos][preNum][sum];

	long long res = 0;
	int end = full ? digit[pos] : 1;
	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, i, sum+(i==preNum && preNum==1), full && i == end);
	}
	if(!full) dp[pos][preNum][sum] = res;
	return res;
}
long long calc(int n)
{
	return dfs(init(n) - 1, 0, 0, true);
}
int main()
{
	int cases, Cas = 0, n;
		memset(dp, -1, sizeof(dp));
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		printf("Case %d: %lld\n", ++Cas, calc(n));
	}
	return 0;
}

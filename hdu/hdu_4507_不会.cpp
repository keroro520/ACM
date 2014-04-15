/*
	不会
	hdu 4507
*/
#include <stdio.h>
#include <string.h>
#define		MOD		1000000007
typedef		long long LL;
LL dp[20][8][8];
int digit[20];

int init(long long x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
long long dfs(int pos, int preSum, LL preNum, bool full)
{
	if(pos == -1) {
		if(preSum % 7 != 0 && preSum != 0 && preNum != 0 && preNum % 7LL != 0) return ((preNum % MOD) * (preNum % MOD)) % MOD;
		return 0;
	}
	if(!full && dp[pos][preSum%7][preNum%7LL] != -1) return dp[pos][preSum%7][preNum%7LL];
	
	LL res = 0, end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) if(i != 7) {
		res = (res + dfs(pos-1, preSum+i, preNum*10 + i, full && i == end)) % MOD;
	}
	
	if(!full) dp[pos][preSum%7][preNum%7LL] = res;
	return res;
}
long long calc(long long n)
{
	int Index = init(n);
	return dfs(Index-1, 0, 0, true);
}

int main()
{
	int cases;
	LL A, B;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d%I64d", &A, &B);
		memset(dp, -1, sizeof(dp));
		printf("%I64d\n", ((calc(B) - calc(A-1)) % MOD + MOD) % MOD);
	}
	return 0;
}

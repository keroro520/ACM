/*
	数位DP简单题
	比模板题多了一维。  开始一直套二维的做法，一直没搞出来，后来想通了余数sum应该单独一维
*/
#include <stdio.h>
#include <string.h>
#define		MAXN	60
#define		FIRST	(0)
int dp[MAXN][3][14], digit[MAXN];

int  init(int x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
int dfs(int pos, int have, bool up_limit, int sum)
{
	if(pos == -1) {
		return have == 2 && sum % 13 == 0;
	}
	if(!up_limit && dp[pos][have][sum] != -1) return dp[pos][have][sum];

	int res = 0, nhave ;
	int end = up_limit ? digit[pos] : 9;

	for(int i = FIRST; i <= end; i++) {
		if(have == 2 || (have == 1 && i == 3)) nhave = 2;
		else if(i == 1) nhave = 1;
		else nhave = 0;

		res += dfs(pos-1, nhave, up_limit && i == end, (sum*10+i) % 13);
	}
	if(!up_limit) dp[pos][have][sum] = res;
	return res;
}
int  calc(int n)
{
	memset(dp, -1, sizeof(dp));
	int Index = init(n);
	return dfs(Index-1, 0, true, 0);
}
int main()
{
	int n;
	while(scanf("%d", &n) != EOF) printf("%d\n", calc(n));
	return 0;
}

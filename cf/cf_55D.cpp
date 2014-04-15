/*
	数位DP  好题  压缩空间
	题意：统计区间内的beautiful number，beautiful number定义：一个正整数能整除它的每个位上的数字(a positive integer number is beautiful if and only if it is divisible by each of its nonzero digits.)

	思路：容易想到要整除每位上的数字，即整除每位上的数字的最小公倍数。
		  比较难想到的一点是压缩：dp[pos][sum][lcm]表前面位的值为sum，最小公倍数的lcm的合法数。但是sum会超int，开不下这么大的数组。看题解知道需要压缩。下面讲压缩：
		  int MOD = LCM(1,2,..9) = 2520
		  按照定义，x为beautiful number：
		    x % LCM{digit[x]} = 0
		  即x % MOD % LCM{digit[x]} = 0

		  而在逐位统计时，假设到了pre***(pre指前面一段已知的数字，而*是任意变)
		    (preSum * 10 + i) % MOD % LCM(preLcm, i)
		  = (preSum * 10 % MOD + i % MOD) % LCM(preLcm, i)

		  另外，还把[1..2520]中能整除2520的数hash成一个下标，因为只有x能整除2520，才有可能在DP做LCM时算出LCM = x。这样，又把dp数组第三维压到了[48]

		  http://www.cppblog.com/Yuan/archive/2011/01/24/139201.html
*/
//cf 55D
#include <stdio.h>
#include <string.h>
#define			MAXN		20
#define			MAXMOD		3000
typedef				long long  LL ;
int digit[MAXN], idx[MAXMOD];
LL dp[MAXN][MAXMOD][48];
int MOD;

int GCD(int a, int b) { return b == 0 ? a : GCD(b, a%b); }
int LCM(int a, int b) { int gcd = GCD(a, b); return a/gcd*b; }
int init(LL x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
void preprocess()
{
	int lcm = 1;
	for(int i = 1; i <= 9; i++) lcm = LCM(lcm, i);
	MOD = lcm;
	int j = 0;
	for(int i = 1; i <= MOD; i++) if(MOD % i == 0) idx[i] = j++;
}
LL dfs(int pos, int preSum, int preLcm, bool full)
{
	if(pos == -1) return preSum % preLcm == 0;
	if(!full && dp[pos][preSum][ idx[preLcm] ] != -1) return dp[pos][preSum][ idx[preLcm] ];

	LL res = 0;
	int end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) {
		int newSum = (preSum * 10 + i) % MOD;			//TODO		妙呀
		int newLcm = (i == 0 ? preLcm : LCM(preLcm, i));
		res += dfs(pos-1, newSum, newLcm, full && i == end);
	}
	if(!full) dp[pos][preSum][ idx[preLcm] ] = res;
	return res;
}
LL calc(LL n)
{
	int Index = init(n);
	return dfs(Index-1, 0, 1, true);
}
int main()
{
	preprocess();
	memset(dp, -1, sizeof(dp));
	int cases;
	LL l, r;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d%I64d", &l, &r);
		printf("%I64d\n", calc(r) - calc(l-1));
	}
	return 0;
}

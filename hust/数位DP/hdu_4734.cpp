/*
	数位DP 好题
	题目大意：给你两个数 a、b，F(x) = An * 2n-1 + An-1 * 2n-2 + ... + A2 * 2 + A1 * 1，A是a十进制各个数位上的数字，让你求出 0 ~ b 中f(x) 比f(a)小的数字个数。
	思路：数位DP。。 d[ i ][ j ]表示没满的的时候前 i 位f(x)<=j的个数，d[ i ][ j ] = SIGMA(d[ i - 1][ j - num[ i ]*c[ i ] ])。
	挺水的数位DP啊，比赛的时候用for做的，因为我们不是预处理的那种，每次都算一遍，T很多，然后一直TLE，无语啊、。。T^T   TLE原因如下：由于都是不满的，所以memset要放外面！
	或者直接for，先预处理，不过要多一维表示该位上的数字是多少，即 d[ i ][ j ][ s ] 表示 前 i 位第 i 位上的数字是 j，<= s 的个数，具体代码看这里吧：http://blog.csdn.net/suvigo/article/details/11689709


	我一开始定义dp[pos][sum]是pos位的数{x}中和为sum的合法数个数，但是会发现这样定义mem(dp,-1)得放在里面，则TLE，所以就需要改变sum的含义，改dp[i][j]为i位的数{ x } 中 F ( x ) 小于 j 的数的个数.
*/
#include <stdio.h>
#include <string.h>
#define	MAXN	15
int dp[MAXN][5000], digit[MAXN];
int bound;
int init(int x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
int F(int A)
{
	int sum = 0, i = 0;
	while(A) {
		sum += (1 << i) * (A % 10);
		i++, A /= 10;
	}
	return sum;
}
int dfs(int pos, bool full, int sum)
{
	if(sum < 0) return 0;
	if(pos == -1) return 1;
	if(!full && dp[pos][sum] != -1) return dp[pos][sum];
	int res = 0;
	int end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) {
		res += dfs(pos-1, full && i == end, sum - (i << pos));
	}
	if(!full) dp[pos][sum] = res;
	return res;
}
int calc(int n)
{
	int Index = init(n);
	return dfs(Index - 1, true, bound );
}
int main()
{
	memset(dp, -1, sizeof(dp));
	int A,B,cases,Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &A, &B);
		bound = F(A);
		printf("Case #%d: %d\n", ++Cas, calc(B));
	}
	return 0;
}

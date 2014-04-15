/*
	环状DP  好题

	题意：给一个环{A}，1 <= ai <= 1000，问有多少种方案，取出连续的一段，使得拼接起来的数字是K的倍数. n <= 50000, k <= 200

	思路：难点就在于对环的处理吧~
		
		  考虑链的情况，dp[i][j] 表示以第i个数结尾，模K为j的方案数，则∑dp[i][0]即方案数

		  接下来考虑环，第1个和第n个是必选的，那么便是一个后缀为前缀，前缀为后缀拼接而成的。
		  所以，枚举每一个前缀，假设当前前缀模K等于j，借助之前的dp[n]，我们可以知道模K为K-j的后缀为dp[n][K-j]个，但是这些后缀中可能有些和当前前缀重叠了，我们要把这些重叠的部分去掉。(我觉得难点就是在于怎么找出对于当前前缀，有多少个模K为K-j的后缀跟它重叠)
		  怎么做呢？爱神的算法挺漂亮的~
		  枚举i，对于当前i：cnt[i的后缀模K]++，设j = i的前缀模K，则以i的前缀为后缀的方案数 = dp[n][K-j] - cnt[K-j]
		  因为每次枚举i我们都对i的后缀的计数加1，所以保证对于后续的i'，cnt里面存的都是与i'的前缀重叠的
		  我擦...看代码吧...都是看爱神的: http://blog.csdn.net/acm_cxlove/article/details/10555913
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		50005
#define		MAXK		205

int n, K, dp[2][MAXK], duplicate[MAXK], fac[MAXN * 3 +  5], a[MAXN], prefix[MAXN], suffix[MAXN], l[MAXN];
int Len(int x)
{
	int len = 0;
	do {
		len++;
		x /= 10;
	} while(x);
	return len;
}
int main()
{
	while(scanf("%d %d", &n, &K) != EOF) {
		fac[0] = 1;
		for(int i = 1; i <= n*3; i++) fac[i] = fac[i-1] * 10 % K;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			l[i] = Len(a[i]);
		}
		memset(dp, 0, sizeof dp);
		int cur = 0;
		long long ans = 0;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < K; j++) dp[cur][j] = 0;
			dp[cur][a[i]%K] = 1;
			for(int j = 0; j < K; j++)
				dp[cur][(j*fac[l[i]] + a[i])%K] += dp[1-cur][j];
			ans += dp[cur][0];
			cur = 1 - cur;
		}
		prefix[0] = 0, suffix[n+1] = 0;
		for(int i = 1; i <= n; i++) prefix[i] = (prefix[i-1] * fac[l[i]] + a[i]) % K;
		int tmp = 0, s = 0;
		for(int i = n; i >= 1; i--) suffix[i] = (a[i] * fac[tmp] +  suffix[i+1]) % K, tmp += l[i];
		memset(duplicate, 0, sizeof duplicate);
		for(int i = 1; i <= n; i++) {
			int p = prefix[i];
			s += l[i];
			duplicate[ suffix[i] ]++;
			for(int j = 0; j < K; j++)				//j是序列后缀，现在充当前缀；p是序列前缀，现在充当后缀，所以是j*fac[s]+p
				if( (j * fac[s] + p) % K == 0 ) ans += dp[1-cur][j] - duplicate[j];	//duplicate[]存的是与当前i的前缀prefix[i]重叠的部分
		}
		printf("%I64d\n", ans);
	}
	return 0;
}

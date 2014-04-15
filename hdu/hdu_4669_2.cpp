/*
	环形DP
	思路：把环加倍变成链，比如原来是 9 6 4 2 8，变成一条链后是 9 6 4 2 8 9 6 4 2
		  dp[i][j]表示以第i个数结尾，向前最多n个珠子，组成的数模K为j的方案数
		  从i = n开始，先O(n)算出dp[n][j]，接下来就是考虑怎样利用dp[i][]转移到dp[i+1][]（因为我们规定dp[i][]表示的是“向前最多n个数”）
		  我是这样考虑的，既然只要前面n个，那转移到i+1的时候，我只要把i-n给消掉就可以了。
		
		  参考题解：http://blog.csdn.net/dyx404514/article/details/9970417


		  我觉得这种解法比爱神的具有通用性，虽说爱神的确实比较漂亮~
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		(50005*2)
#define		MAXK		205

int dp[2][MAXK], fac[MAXN * 3], a[MAXN], l[MAXN];
int n, K;
int calc(int x)
{
	int len = 0;
	while(x) {
		len++, x /= 10;
	}
	return len;
}
int main()
{
	while(scanf("%d %d", &n, &K) != EOF) {
		fac[0] = 1;
		for(int i = 1; i <= 3*n; i++) fac[i] = fac[i-1] * 10 % K;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), l[i+n] = l[i] = calc(a[i]), a[i+n] = a[i];
		
		memset(dp, 0, sizeof dp);
		int tmp = 0, len = 0, cur = 0, ans = 0;
		for(int i = n; i >= 1; i--) {
			tmp = (tmp + a[i] * fac[len]) % K;
			len += l[i];
			dp[cur][tmp]++;
		}
		ans += dp[cur][0];
		dp[cur][tmp]--;					//去掉a[1]之后，dp[n][ a1a2a3..an % K ]--，因为现在tmp代表的就是a1a2a3..an
		len -= l[1];
		tmp = ((tmp - a[1] * fac[len]) % K + K) % K;		//去掉a[1]之后的前缀

		for(int i = n+1; i < 2*n; i++) {
			cur = 1 - cur;
			for(int j = 0; j < K; j++) dp[cur][j] = 0;
			dp[cur][a[i]%K]++;
			
			for(int j = 0; j < K; j++) dp[cur][(j * fac[l[i]] + a[i]) % K] += dp[1-cur][j];

			len += l[i];
			tmp = (tmp * fac[l[i]] + a[i]) % K;				//加了ai 之后的新的前缀tmp

			ans += dp[cur][0];

			dp[cur][tmp] --;								//现在要去掉a[i-n+1]，所以dp[n][a(i-n+1)a(i-n+2)..ai] --
			len -= l[i-n+1];
			tmp = ((tmp - a[i-n+1] * fac[len]) % K + K) % K;	//去掉a[i-n+1]之后的新的前缀tmp
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*
	0/1背包统计方案  好题
	题意：有n件物品，每件都有价值，用m的钱买这些物品，。尽可能多的买东西，（直到钱不够买其他的东西为止）。问有多少种买东西的方法。。

	思路：摘抄：http://blog.csdn.net/scorpiocj/article/details/6607580
			考虑什么情况下一个都放不进去，就是剩下物品中体积最小的那个（体积为v)都放不进去，即背包装载容量应为[V-v+1,V]

			那么我们可以将物品按容量排序，从小到大枚举不放入背包的体积最小的，那么此时比它小的物品都应该放入背包中，我们可以对剩下的i+1到n的物品做01背包，然后将可行的方案统计出来，这样，第i件物品考虑了i-1次，总复杂度为O(n^2*V)

			n较大的话会超时，我们可以反过来做，每个物品只放入背包中一次，即枚举的时候从最大的开始，先统计此时的方案数，然后将物品放入背包，这样一直下去，总复杂度O(n*V)

			具体可以参见《浅谈几类背包问题》


			
			看不会优化的部分，所以只写了n^2 * V的。
*/
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN	1005
int dp[MAXN], a[MAXN], sum[MAXN];
int n, m;
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		sort(a+1, a+n+1);
		if(a[1] > m) {
			printf("%d 0\n", ++Cas);
			continue;
		}
		for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i];
		long long ans = 0;
		for(int u = 1; u <= n; u++) {
			memset(dp, 0, sizeof(dp));
			dp[0] = 1;
			for(int i = u+1; i <= n; i++)
				for(int j = m - sum[u-1]; j >= a[i]; j--)
					dp[j] += dp[j-a[i]];
			for(int j = max(0, m - sum[u-1] - a[u] + 1); j <= m - sum[u-1]; j++)
				ans += dp[j];
		}
		printf("%d %I64d\n", ++Cas,ans);
	}
	return 0;
}

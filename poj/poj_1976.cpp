/*
	思路题  序列DP
	题意：一个数列，n个数，找三个 m个连续数的子数列，使其和最大。

	思路：找3个连续子数列。那其实我们可以一个一个找，在找了第一个的基础上找第二个，在找了第二个基础上找第三个。
		  dp[1][i] 表在1-i中找第一个m子序列的最优值
		  dp[2][i] 表在1-i中找第二个子序列的最优值
		  dp[3][i] 表在1-i中找第三个子序列的最优值
		  
		  dp[2][i] = dp[1][j] + sum{a[i-m+1],a[i-m+2]...a[i]} , j <= i-m

		  改方程需要枚举j，复杂度很大，但正如之前所说，因为我们找第2个m序列是建立在找了第1个m序列的基础上的。我们可以用O(n)的时间预处理初个pre[i]记录1-i中最大的dp[1][j](1 <= j <= i)，这样，我们就不用枚举j了，直接就dp[2][i] = dp[1][pre[j-m]] + sum{a[i-m+1],a[i-m+2]...a[i]}
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define		MAXN		50005
int a[MAXN], sum[MAXN], dp[3][MAXN], pre[MAXN];
int n;
int main()
{
	int cases, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i-1] + a[i];
		scanf("%d", &m);

		for(int i = m; i <= n; i++) dp[0][i] = sum[i] - sum[i-m]; 
		
		pre[m-1] = 0;
		for(int i = m; i <= n; i++) pre[i] = max(dp[0][i], pre[i-1]);
		for(int i = 2*m; i <= n; i++) dp[1][i] = sum[i] - sum[i-m] + pre[i-m];

		pre[2*m-1] = 0;
		for(int i = 2*m; i <= n; i++) pre[i] = max(dp[1][i], pre[i-1]);
		for(int i = 3*m; i <= n; i++) dp[2][i] = sum[i] - sum[i-m] + pre[i-m];

		int ans = 0;
		for(int i = 3*m; i <= n; i++) ans = max(ans, dp[2][i]);
		printf("%d\n", ans);
	}
	return 0;
}

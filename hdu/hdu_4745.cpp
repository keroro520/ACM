/*
	区间DP  最长回文子序列
	http://fszxwfy.blog.163.com/blog/static/44019308201381585813745/
	题意：给定一个串，求从任意两个起点分别朝着两个方向走，形成的两个串的最长公共子序列的最大值是多少。且走到串尾可再回到串头，但不能超过其起始位置。

	解法：就是求最长回文子串，枚举起点，针对每个起点，两边的最长回文串的长度之和就是当前情况下的值。
      	  而且显然当两个兔子的起点相邻时肯定可以得到一种情况是最优解，因为假设在取得最优解时两个起点的其距离为len,当len内无最长回文子串时，我们将两个起点移到其中间的两个相邻的位置时显然值不变。
          当len内涉及最长回文子串时，得到的结果可能会改变顺序，但至少会有一种情况得到得长度与之前相同，显然当移到两个起点时移过涉及最长回文子串的点数相同时，得到的最值结果只是将这些点改变下顺序。
          当移过的点数不同时，同样也是，只需调整配对的顺序即可。假设分别移过了x,y个点，则len里任然有min(x,y)个点可以相互配对，其中一边多的部分任然与之前在len之外的点配对，这过程可能会跳过一些原来需要配对的点，对于这些点交换顺序即可（原来a，b两个位置可以配对，a原来是在向左时被选中，则此次选择在向右时选a，同理b).
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define		MAXN	1005
int dp[MAXN][MAXN], a[MAXN], n;
int main()
{
	while(scanf("%d", &n) && n) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= n; i++) dp[i][i] = 1;
		for(int i = n; i >= 1; i--)
			for(int j = i+1; j <= n; j++) {
				dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
				if(a[i] == a[j]) dp[i][j] = max(dp[i][j], dp[i+1][j-1] + 2);
			}
		int ans = 0;
		for(int i = 1; i <= n; i++) ans = max(ans, dp[1][i] + dp[i+1][n]);
		printf("%d\n", ans);
	}
	return 0;
}
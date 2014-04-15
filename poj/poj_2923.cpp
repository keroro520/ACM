/*
	状压DP  背包问题  好题

	题意：n(n<=10)件物品，每件物品重ai。两辆容量分别为C1,C2的车。要把这n件物品搬到另外一个地方（两辆车都是一起的）问最少搬几趟？

	思路：初看根本没思路，就算看数据范围知道是状压也完全没思路，想记忆化搜，但也不知道怎么搜。
		  
		  预处理出每一种状态是否能一趟运走。这个判断用0/1背包来搞就可以了。
		  接下来是核心。还是0/1背包，dp[T]表状态T最少运几趟，则dp[T] = min{ dp[S] + 1 } | T能由S再加一趟达到。



	涨见识了。背包问题改为求几趟竟然要这么麻烦的状压...
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[1 << 11], a[11];
bool s[1 << 11], f[100*20];
int n, C1, C2;
bool check(int x)
{
	memset(f, false, sizeof(f));
	f[0] = true;
	int sum = 0;
	for(int i = 0; i < n; i++) if((1 << i) & x) sum += a[i];
	if(sum > C1 + C2) return false;
	for(int i = 0; i < n; i++) if((1 << i) & x) {
		for(int j = C1; j >= a[i]; j--)
			if(f[j-a[i]]) f[j] = true;
	}
	for(int j = C1; j >= 0; j--) if(f[j]) return sum-j <= C2;
	return sum <= C2;
}

int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d%d", &n, &C1, &C2);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		s[0] = true;
		for(int i = 1; i < (1 << n); i++) 
			s[i] = check(i);
		memset(dp, 127, sizeof(dp));
		dp[0] = 0;
		for(int i = 1; i < (1 << n); i++) {
			if(s[i]) {
				dp[i] = 1;
				continue;
			}
			for(int j = 0; j < i; j++) if((i | j) == i) {
				int k = i - j;
				if(s[k]) dp[i] = min(dp[i], dp[j] + 1);
			}
		}
		printf("Scenario #%d:\n%d\n\n", ++Cas, dp[(1 << n) - 1]);
	}
	return 0;
}

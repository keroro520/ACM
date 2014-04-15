/*
	差值博弈  极大极小  博弈DP
	题意：一堆数，两个小朋友，轮流从堆里面取数，要求第一个人取的数在[a,b], 0 <= a <= b区间内，每次取的数x和前一次(也就是对方)取的数y满足a <= x-y <= b。两人都想使得自己取得的数总和减去对方的总和的差值尽量大，问最后第一个小朋友减去第二个小朋友的差值最大为多少？

	思路：差值博弈
		  易推出后面取的数总是比前面取的数大，所以先排序
		  dp[i]表当前选手确定选了i之后，可以达到的最大分差
		  两人都想让自己的与对方的分差尽量大，而当前选手选了i之后，是轮到对方选。假设当前选手A选了i之后，先手变成了对方B，那B当然在后面的状态种也是要使得自己与A的分差尽量大，所以A选了i的最优分差A-B = num[i] - max{DP(j)}
		   即dp[i] = num[i] - max{ dp[j] } , a <= num[j] - num[i] <= b

		   算法是，枚举先手取的第一个数，然后记忆化dp。




		   感觉这种差值博弈就是，假设先手A取了i，接着后面B对方因为要使得A-B最小，所以B就会选一个最大的dp[j]，使得A-B = min{ num[i] - dp[j] } = num[i] - max{dp[j]}

		   * ****************************************************** *
		   * 题目要求先手的最大值，可以转化为求先手-后手的最大值    *
		   *														*
		   * dp[i]表示先手面临状态i时，先手进行决策后，先手-后手的最*
		   * 大值													*
		   * 程序在进行递推时，状态要从后往前进行枚举。也可以采用记 *
		   * 忆化搜索的方式，正向思考比较方便						*
		   *														*
		   * ****************************************************** *

*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
const int inf = (1 <<  28);
int dp[MAXN], num[MAXN], a, b, n;
int DP(int now)
{
	if(dp[now] != -inf) return dp[now];
	int ans = -inf;

	for(int i = now+1; i < n; i++) if(num[i] - num[now] >= a) {
		if(num[i] - num[now] > b) break;
		ans = max(ans, DP(i));
	}

	if(ans == -inf) ans = 0;		//说明后面没有数可以选了
	return dp[now] = num[now] - ans;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d %d", &n, &a, &b);
		for(int i = 0; i < n; i++) dp[i] = -inf;
		for(int i = 0; i < n; i++) scanf("%d", &num[i]);
		sort(num, num+n);
		int ans = -inf;
		for(int i = 0; i < n; i++) if(a <= num[i] && num[i] <= b) 
				ans = max(ans, DP(i));
		if(ans == -inf) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}

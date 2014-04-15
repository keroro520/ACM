/*
	差值博弈  极大极小  状压DP   好题  实现  
	题意：题目大意：有G种颜色的宝石，B（B<=21）个背包，每个背包中有一些宝石。Alice和Bob轮流每次拿走一个背包，把背包中的宝石放进熔炉中。当一名角色X把一个背包中的宝石放进熔炉中后，熔炉中某种颜色的宝石有S个，那么这S个宝石变成一颗魔法石，角色X获得这颗魔法石（如果形成了多颗魔法石，角色X获得多颗魔法石）。如果角色X在某一轮中获得了魔法石，那么他可以接着额外进行一轮游戏，如果在额外的一轮游戏中，又获得了魔法石，那么他又可以继续进行一轮游戏。游戏一共进行B轮，若两人都采取最优策略，求游戏结束后，Alice获得魔法石数量-Bob获得魔法石数量的最大值。Alice先进行游戏。

	思路：
	  	  实现比较好看，我是抄的
		  dp[i]表还没拿走的状态为i，先手-后手的最大差值
		  dp[(1<<B)-1] = 0
		  分情况转移，tp = get(j->i), get(j->i)表示在状态j的情况下取了背包x能获得的魔法石数量
		  tp > 0 : 
		  	dp[i] = max{dp[j] + get(j->i)}			//j状态取了背包x后变成状态i
		  tp = 0 :
		  	dp[i] = max{-dp[j]}
		  状态转移用的是递推

		  我觉得最好的部分是预处理出get(j->i)这部分，我就是死活写不出来，看题解的。
		  low(x) 	 : x为1的最低位
		  x ^ low(x) : x去掉为1的最低位 

		  get[i][j] 表状态i中共有j类宝石的个数，get[i][j] = get[pre][j] + num[cur][j]，其中pre状态取了cur包后变成状态i
		  sum[i] 表示状态i一共可以拿的魔法石个数，sum[i] = ∑(get[i][j] / S), j = 1..G
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		low(x)		((x) & (-(x)))

int G, B, S, Log[(1<<21)+13], dp[(1<<21)+13], sum[(1<<21)+13], get[(1<<21)+13][11], num[22][11];
int main()
{	
	int x, c;

	Log[0] = -1;
	for(int i = 1; i <= (1 << 21); i <<= 1) Log[i] = Log[i>>1] + 1;
	while(scanf("%d %d %d", &G, &B, &S), G || B || S) {
		memset(num, 0, sizeof num);
		for(int i = 0; i < B; i++) {
			scanf("%d", &c);
			while(c--) {
				scanf("%d", &x);
				num[i][x]++;
			}
		}
		memset(get[0], 0, sizeof get[0]);
		for(int oo = (1 << B), i = 1; i < oo; i++) {
			int pre = i ^ low(i), cur = Log[low(i)];
			for(int j = 1; j <= G; j++)
				get[i][j] = get[pre][j] + num[cur][j];
		}
		for(int oo = (1 << B), i = 0; i < oo; i++) {
			sum[i] = 0;
			for(int j = 1; j <= G; j++)
				sum[i] += (get[i][j] / S);
		}
		
		memset(dp, 128, sizeof dp);
		dp[(1<<B) - 1] = 0;
		for(int i = ((1<<B)-1); i >= 0; i--) {
			for(int j = i; j; j -= low(j)) {
				int pre = i ^ low(j);
				int tp  = sum[i] - sum[pre];
				if(tp) dp[pre] = max(dp[pre], dp[i] + tp);
				else   dp[pre] = max(dp[pre], -dp[i]);
			}
		}
		printf("%d\n", dp[0]);
	}
	return 0;
}

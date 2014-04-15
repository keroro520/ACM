/*
	状压DP  TSP  旅行商问题  最短路  实现   经典题   好题

	题意：无向边权图，从城市1带着M元钱开始出发，遍历给定的H个城市，而且到达这H个城市必须要有足够的钱di买护照，再在这个城市打工赚得ci元。
		  也就是说这H个城市是给出的，是一定要在这里买护照并且打工一次的，无强制顺序（选定的H个城市须且仅能买一次护照打一次工），其它城市无所谓要不要经过。每个城市可以到达多次。如果城市1在被选定的城市里面，则不一定要先在城市1打工。
		  问是否有线路可以实现从城市1出发再回到城市1

	思路：比赛的时候被题意给坑了...
		  理解清楚题意就是裸TSP问题了.

		  看cxlove的题解，floyed搞出最短路
		  dp[i][x] 表状态S，最后到达的城市为i 的最优值

		  状态转移不说，就是觉得cxlove的初始化很巧妙。如果城市1不在给出的H个城市{X}里面，他就把城市1添加进{X}里面，c/d值都为0，这样就省去了很多考虑这儿考虑那儿的麻烦
		  有些细节，我觉得我是想不到的。cxlove实现得很漂亮


		  !!! 用memset() 初始化会在计算的时候溢出...跪...

		  TSP问题：http://blog.csdn.net/gfaiswl/article/details/4749713
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			inf			(1 << 28)
int path[105][105];
int choose[18], c[18], d[18], dp[18][(1 << 17) + 3];
int n, m, money, H;

void init()
{
	//memset(path, 127, sizeof(path));			//!!! 这点很重要啊！这样memset初始化在计算的时候有可能会溢出，然后就跪了！！！
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) path[i][j] = inf;
	//for(int i = 0; i <= n; i++) path[i][i] = 0;		//need ? 不需要
}
int main()
{
	int cases, u, v, w;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d %d", &n, &m, &money);
		init();
		while(m--) {
			scanf("%d %d %d", &u, &v, &w);
			u--, v--;
			if(w < path[u][v]) path[u][v] = path[v][u] = w;
		}
		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++) if(k != i)
				for(int j = 0; j < n; j++) if(i != j && k != j)
					if(path[i][k] + path[k][j] < path[i][j]) path[i][j] = path[i][k] + path[k][j];
		
		scanf("%d", &H);
		int s = -1;
		for(int i = 0; i < H; i++) {
			scanf("%d %d %d", &choose[i], &c[i], &d[i]); choose[i] --;
			if(choose[i] == 0) s = i;
		}

		if(s == -1) {												//这一步好妙			//细节
			choose[H] = 0, c[H] = d[H] = 0;		//起点
			s = H++;
		}
		
		memset(dp, -1, sizeof dp);
		if(money >= d[s]) dp[s][1 << s] = money - d[s] + c[s];		// 这步很重要也很容易忘记		//细节
		dp[s][0] = money;		//这一步需要吗？？？？？
								//难道说如果点1被选定，可以先不在点1买护照打工，而是先跑到别的城市吗...?  yes

		for(int S = 0; S < (1 << H); S++)
			for(int i = 0; i < H; i++) if(dp[i][S] != -1)		//因为第一个工作的城市不一定是1...blabla，所以不能if(S & (1<<i)) // 细节
				for(int j = 0; j < H; j++) if(!((1 << j) & S))
					if(dp[i][S] >= path[choose[i]][choose[j]] + d[j]) {
						int T = (S | (1 << j));
						dp[j][T] = max(dp[j][T], dp[i][S] - path[choose[i]][choose[j]] - d[j] + c[j]);
					}
		bool flag = false;
		for(int i = 0; i < H; i++) 
			if(dp[i][(1 << H)-1] >= path[choose[i]][0]) flag = true;
		puts(flag ? "YES" : "NO");
	}
	return 0;
}

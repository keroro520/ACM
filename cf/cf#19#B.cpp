/*
  	背包DP  融合了两种信息  融合信息  改变状态  好题  思路题  启发

	题意：一个小偷去商店买N件商品，只有一个售货员，售货员处理商品i用时ti(ti>=0)，售价ci。这个
        小偷可以趁售货员处理商品的时候偷走剩下还没处理的任意商品，一秒钟可以偷走一件，而处
        理商品的顺序是小偷决定的。你的任务就是帮助小偷决定给售货员处理商品的顺序，使得小偷
        要交的费用最少，输出最少费用。

	思路：直接记录题解的一些点
		  每个ti加一，问题就变为“n件物品，重量ti>0, 价钱ci>0。取若干件物品，要求满足总重量不小于n时，
		  总价钱最少”
		
		  一直想不明白ti+1为什么正确以及怎么想出来的。neko刚才跟我说他刚才是怎么AC的的过程，受益良多
		  首先说正确说法：我们记{X}为付钱的物品，{Y} = N - X为偷的物品，
		  则需要满足 Σtx >= Y，x∈{X}
		  应该要想到 |X| + Σtx >= N
		
		  想DP的时候发现对于dp[i][j]表前i个物品耗费时间为j的最小花费，既要记录最小耗费Σcx，又要记录
		  {X}的个数（因为要Σtx >= N-|X|），就不知道怎么办。因为我们一般的DP不会需要记录前i件物品取
		  了多少件。
		  继而就发现，我们可以把式子|X| + Σtx >= N变为 Σ(tx+1) >= N，而且还跟{Y}无关！所以t+1这个想
		  法就出来了。
		
		  有了t+1，问题就变成0/1背包了。
		
		
		  拓展：其实这就是一种“融合信息“的方法，把”耗费时间”和”选取的物品个数”这两个信息融合到一个
		        量里面。
		
		        neko还告诉我上次中南月赛时有种很吊的“融合”信息的方式。题目是这样的，求一个二分图网
		        络流，如果流相等的话要经过X部的点最多，还有什么无穷大边blabla~ 题解是这样搞的，每条
		        边边权*10000，连接X部的边边权+1，这样，我们就把每个节点的权值分两部分，高位是流大小，
		        低4位是经过X部的点数目，这样我们就可以直接套网络流的模板了。
		        另一题是最短路加点拓展，一个DAG图有边权有点权，要求找一条路径，满足边权最小，边权同样
		        小的情况下点权最大。我们可以把边权*10000，点拆成两个点，连上边，边权为原点权取负。
		        这样我们就可以直接套最短路模板了。（Neko比赛时的做法更好玩，先求边权最短路，再在该
		        最短路图上求点权最长路）
		        这样“融合”两种信息多数情况下是为了方便编码，因为可以直接套模板。
		
			再记录一点，0/1背包可以有个优化，就是先sort一遍，然后用个sum记录前i件物品的权值和，
			枚举j时for(j = min(sum,m); j >= 0; j--) ...
*/
//http://codeforces.com/contest/19/problem/B
int main()
{
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d%I64d", &t[i], &c[i]);

  //f[j]  花费j时间能得到的最小花费
  memset(f, 127, sizeof(f));
  f[0] = 0;
  for(int i = 1; i <= n; i++) {
    t[i]++;
    for(int j = n+2000; j >= 0; j--) {
      if(j >= t[i]) f[j] = min(f[j], f[j-t[i]]+c[i]);
//        f[j] = min(f[j], f[max(0, j-t[i])]+c[i]);
    }
  }
  ll ans ; memset(&ans,127,sizeof(ans));
  for(int i = n; i <= n+2000; i++) ans = min(ans, f[i]);
  printf("%I64d\n", ans);
  //printf("%I64d\n", f[n]);
  return 0;
}



#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef long long ll;
#define MAXN 2005
int n, t[MAXN];
ll INF, c[MAXN], f[MAXN+MAXN];

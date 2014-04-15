/*
	博弈  anti-sg   SJ定理       好题
	题意：今有若干堆火柴，两人依次从中拿取，规定每次只能从一堆中取若干根，可将一堆全取走，但不可不取，最后取完者为负

	思路：anti-sg，直接用SJ定理，详见《组合游戏略述——浅谈SG游戏的若干拓展及变形  --贾志豪》

		  [定理](SJ 定理)
		  对于任意一个 Anti-SG 游戏,如果我们规定当局面中所有的单一游
		  戏的 SG 值为 0 时,游戏结束,则先手必胜当且仅当:(1)游戏的 SG 函
		  数不为 0 且游戏中某个单一游戏的 SG 函数大于 1;(2)游戏的 SG 函数
		  为 0 且游戏中没有单一游戏的 SG 函数大于 1。

		  另外，发现这道题sg[n] = n...

		  http://blog.csdn.net/acm_cxlove/article/details/7854530  有证明，没心情看，直接用SJ了..
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN		4748
int SG(int n)
{
	return n;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		int all = 0, single = 0, n, x;
		scanf("%d", &n);
		while(n--) {
			scanf("%d", &x);
			int res = SG(x);
			all ^= res, single = max(single, res);
		}
		if( (all != 0 && single > 1) || (all == 0 && single <= 1) ) puts("John");
		else	puts("Brother");
	}
	return 0;
}

/*
	博弈  二维sg  好题
	题意：n堆石子，每次可以有两种操作：1、拿走一颗石子。2、将两堆石子合并
	思路：
		  之前做过一堆可以分成两堆的，但是两堆合成一堆的就不知道怎么做了。看了题解，知道需要分析一些东西，感觉自己在现场赛肯定做不出来

		  假设所有堆都有多余1的石子，则因为每次可以拿走一颗石子变成sum-1，也可以合并变成sum，即奇偶性试试可以随意确定的（合并a堆和b堆的石子相当于对一堆(a+b+1)的石子减1）
		  “然而，特殊情况出现了。当某些堆石子只有一颗的时候呢？只要本来要输的那个人有机会将这颗石子拿走，本来要赢的那个孩子就没有机会将这一堆合并了！整体奇偶性一改变，输家可能变成了赢家！” （无法逆转奇偶）

		  sg[x][y]表有x堆石子数为1的堆，y代表剩下的∑ai+tot-1, ai>1, tot为ai>1的堆数
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN (1005 * 55)
int sg[55][MAXN];
int SG(int x, int y)
{
	if(x == 0) return y&1;
	if(sg[x][y] != -1)   return sg[x][y];
	if(y == 1) return sg[x][y] = SG(x+y, 0);				//不加这一句就会WA，为什么？
	bool vis[7];
	memset(vis, false, sizeof vis);
	if(x >= 2) vis[ min(5, SG(x-2, y+2+(y?1:0))) ] = true;
	if(x >= 1 && y > 0) vis[ min(5, SG(x-1, y+1)) ] = true;
	if(x >= 1) vis[ min(5, SG(x-1, y  )) ] = true;
	if(y >= 1) vis[ min(5, SG(x,   y-1)) ] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[x][y] = i;
}
int main()
{
	int cases, Cas = 0, n;
	memset(sg, -1, sizeof sg);
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		int x = 0, y = 0, z, ans = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &z);
			if(z == 1) x++;
			else	   y += z+1;
		}
		if(y) y--;
		ans = SG(x, y);
		printf("Case #%d: %s\n", ++Cas, ans ? "Alice" : "Bob");
	}
	return 0;
}

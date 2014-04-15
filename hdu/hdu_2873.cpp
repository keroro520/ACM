/*
	博弈  二维sg
	
	看视频~直接抄网上题解了~~~

	题目描述；给你一个n*m的格子（横纵都是从1开始编号的），格子中间会有.或者#(假设坐标是x,y)，#代表炸弹，炸弹有如下性质：
	  1.x>1且y>1时，可以分成两个炸弹，要求就是第一个是(1~x-1,y)中的一个，第二个是(x,1~y-1)中的一个
	  2.x=1或者y=1的时候，只能分裂出来一个。
	  3.炸弹在（1,1）或者两个炸弹同时在一个格子时候会爆炸。
	  两个人轮流操作，不能操作者失败，问谁胜利。

	解法：弄了一个看起来非常逼真的sg函数，虽然还没弄懂呢，但是这样就过了。。。求出每个点的sg值，然后异或，然后就没然后了。。。

*/
#include <string.h>
#include <stdio.h>
#define	MAXN 55
int sg[MAXN][MAXN];

int SG(int row, int col)
{
	if(row == 1 && col == 1) return 0;
	if(sg[row][col] != -1)   return sg[row][col];
	bool vis[MAXN * MAXN];
	memset(vis, false, sizeof vis);
	if(row == 1) for(int i = 1; i < col; i++) vis[ SG(row,i) ] = true;
	if(col == 1) for(int i = 1; i < row; i++) vis[ SG(i,col) ] = true;
	for(int i = 1; i < row; i++)
		for(int j = 1; j < col; j++)
			vis[ SG(i,col) ^ SG(row,j) ] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[row][col] = i;
}
char str[100];
int main()
{
	int n, m;
	memset(sg, -1, sizeof sg);
	while(scanf("%d %d", &n, &m) , n || m) {
		int ans = 0;
		for(int i = 1; i <= n; i++) {
			scanf("%s", str+1);
			for(int j = 1; j <= m; j++) if(str[j] == '#') {
				ans ^= SG(i, j);
			}
		}
		puts(ans ? "John" : "Jack");
	}
	return 0;
}

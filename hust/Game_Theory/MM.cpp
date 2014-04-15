/*
	博弈  棋盘博弈  好题  SG的0/1性质

	题意：题意：给你一个n*m的矩形，0表示空着的，1反之，现在两个人轮流放2*2的矩形，谁不能放了，谁就输了。

	思路：sg
		  从这道题知道了SG在“如果必胜态的所有后继都是必败态”情况时，SG是具有0/1性质的。也就是说，只要知道状态S的某一邻接状态(S->T)为0，则S的sg肯定为1.
*/
//hdu 1760
#include <stdio.h>
#define			MAXN		55

int n, m, a[MAXN][MAXN];
bool check(int i, int j)
{
	return ! (a[i][j] || a[i][j-1] || a[i-1][j] || a[i-1][j-1]);
}
void label(int i, int j)
{
	a[i][j] = a[i][j-1] = a[i-1][j] = (a[i-1][j-1] ^= 1);
}
bool SG()
{
	for(int i = 2; i <= n; i++)
		for(int j = 2; j <= m; j++) if(check(i, j)) {
			label(i, j);
			if(!SG()) {
				label(i, j);
				return true;
			}
			label(i, j);
		}
	return false;
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
		puts(SG() ? "Yes" : "No");
	}
	return 0;
}

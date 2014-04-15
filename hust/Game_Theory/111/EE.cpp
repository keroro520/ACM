/*
	博弈 打表 对称
	题意：给一个N，游戏初始有数字num = 1，让游戏者不断乘2-9，谁最先让num >= N谁就赢。

	思路：打个sg表，看有规律就直接水了。
		  还不理解其性质/证明...
*/
//hdu 1517
#include <stdio.h>  

long long limit[20];
int top = 9;
bool check(long long n)
{
	for(int i = 0;i < top; i++) if(n > limit[i] && n <= limit[i]*2) return true;
	return false;
}
int main()
{
	long long n;
	limit[0] = 9;
	for(int i = 1; i < 9; i++)	limit[i] = limit[i-1] * 2 * 9;

	while(scanf("%I64d", &n) != EOF) {
		puts(!check(n) ? "Stan wins." : "Ollie wins.");
	}
	return 0;
}

/*

打表程序
#include <limitio.h>
#include <string.h>
#define		MAXN		1000000
int sg[MAXN];
int SG(int u)
{
	if(u <= 1) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(vis));
	for(int i = 2; i <= 9; i++) vis[SG( ((u-1)/i+1) )] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
int main()
{
	memset(sg, -1, sizeof(sg));
	for(int i = 1; i < MAXN; i++) {
		//printf("%3d:%d\n", i, SG(i));
		if(SG(i) == 0 && SG(i-1) ) printf("# %d\n", i);
		else if(SG(i) != 0 && SG(i-1) == 0) printf("$ %d\n\n", i);
	}
	return 0;
}
*/

/*
	博弈  Anti-SG  SG定理   Anti-Nim  

	题意：有n堆苹果，每堆有mi个。两人轮流取，每次可以从一堆苹果中取任意连续个苹果，最后取光者为输。Fra先下，问是否可以获胜。

	思路：用下下面的代码打了一个sg表，表示我和我的小伙伴们都惊呆了，sg(i) = i...
		  参看《组合游戏略述——浅谈SG游戏的若干拓展及变形---贾志豪》。

		  SJ定理：Anti-SG游戏的必胜态：(1)游戏的sg函数不为0且游戏种的某个单一游戏的sg大于1    (2)游戏的sg函数为0且没有单一游戏的sg大于1
		  					
*/
//hdu 2509
#include <stdio.h>
int n, x;

int main()
{
	while(scanf("%d", &n) != EOF) {
		int ans = 0;
		bool flag = false;
		while(n--) {
			scanf("%d", &x);
			ans ^= x;				//因为这道题的sg(i) == i
			if(x > 1) flag = true;
		}
		puts( (ans && flag) || (!ans && !flag) ? "Yes" : "No");
	}
	return 0;
}



/*
#include <stdio.h>
#include <string.h>
#define		MAXN		1005
int sg[MAXN];

int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= u; i++) {		//取的个数
		for(int j = 0; j <= u-i; j++)		//左边剩下的个数
			vis[ SG(j) ^ SG(u-i-j) ] = true;
	}
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
int main()
{
	memset(sg, -1, sizeof(sg));
	for(int i = 0; i < 60; i++) {
		printf("%2d : %d\n", i, SG(i));
	}
	return 0;
}
*/

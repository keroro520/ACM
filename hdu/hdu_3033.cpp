/*
	0/1背包扩展		好题	用“是否合法”来保证“至少取m个”
	题意：K种品牌的鞋子，每种品牌都至少要买一双。给出每双鞋子的品牌，价钱，价值，求m元能买到多大价值。

	思路：人家只是用了“组”这个概念而已，哪是什么分组背包呀...还是称0/1背包比较靠谱。
		 
		  难点在于“每种品牌至少一双”，也就是每组至少取一个。
		  保证每个分组至少取一件，f[K][m]表示前K种品牌话费了m元钱能买多大价值，先初始化f[][]为-1，f[0][]为0。每次更新f[k][j]时判断一下它的前继状态是否为-1，如果不为-1，说明前继合法，可以递推到f[k][j].
		  f[k][j]的前继有两个（假设现在循环到物品i）：
		  	f[k-1][j-p[i]] != -1	:	在前k-1种品牌上花j-p[i]元 已经满足题目的“前k-1种品牌每种品牌至少一双” ，是合法状态
			f[k][j-p[i]]   != -1	:	在前k种品牌花j-p[i]元，已经满足题目的条件，合法状态

		  如果再来扩展“每种品牌至少两双”呢？加一维就好了呗。
		  用“是否合法”来保证“至少取m个”真是个好方法。

		  另外这个题的数据有点巨神的地方，就是price能为0！！！为0的话状态转移的时候就要注意顺序。对于f[k][j]，要先从f[k][j-p[i]]转移，然后再从f[k-1][j-p[i]]转移，因为这样才能保证price=0时同一件物品没有被多次取过。
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
struct Shoe {
	int price, brand, value;
} a[105];
int f[15][10005];
int main()
{
	int n, m, K;
	while(scanf("%d%d%d", &n, &m, &K) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].brand, &a[i].price, &a[i].value);
		memset(f, -1, sizeof(f));
		for(int i = 0; i <= m; i++) f[0][i] = 0;

		for(int i = 1; i <= K; i++)
			for(int k = 1; k <= n; k++) if(a[k].brand == i)
				for(int j = m; j >= a[k].price; j--) {
					if(f[i][j-a[k].price] != -1) 		//决定取当前第 i 个牌子时要取多少件以及怎样得到最优值
						f[i][j] = max(f[i][j], f[i][j-a[k].price] + a[k].value);
					if(f[i-1][j-a[k].price] != -1)		  //用于承接上一个品牌时的状态
						f[i][j] = max(f[i][j], f[i-1][j-a[k].price] + a[k].value);
				}
		if(f[K][m] == -1) puts("Impossible");
		else printf("%d\n", f[K][m]);
	}
	return 0;
}

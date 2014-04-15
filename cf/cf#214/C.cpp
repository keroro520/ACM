// 好题  背包DP
/*
	题意：n种食物，有ai好吃值，bi卡路里。想要做道沙拉，要求选出来的食物满足∑aj / ∑bj == k。
	      问在满足上述条件下∑aj的最大值。

	思路：∑aj / ∑bj == K，即∑aj == ∑(bj * k)，即∑(aj - bj * K) == 0
		  所以题目就变成了选出若干种食物使得总好吃值∑aj 等于总卡路里值*k 相等

		  一开始我想到“搭建双塔”的做法，但是这里跟双塔不同，这里一个物品有两种属性，选了该物品就得选它的两种属性。
		  所以我就想有什么办法变成一种属性，或者融合起来之类的。

		  物品变成单价为 ai-bi*k，价值为ai，0/1背包求总单价为0，价值最大。

		  注意一下0/1背包的方向，因为ai-bi*k有正负之分，为正时逆向，为负时正向。
*/
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
int f[200 * 10 * 100 + 10000], a[105], b[105];
int n, K, inf;
int main()
{
	memset(&inf, 128, sizeof(inf));
	scanf("%d %d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &b[i]), b[i] *= K;
	for(int i = 1; i <= n; i++) b[i] = a[i] - b[i];

	memset(f, 128, sizeof(f));
	f[100 * 10 * 100] = 0;

	for(int i = 1; i <= n; i++)
		if(b[i] >= 0) {
			for(int j = 200000; j >= 0; j--) if(f[j] != inf) {
				if(j + b[i] >= 0) f[j+b[i]] = max(f[j+b[i]], f[j] + a[i]);
			}
		} else {
			for(int j = 0; j <= 200000; j++) if(f[j] != inf) {
				if(j + b[i] >= 0) f[j+b[i]] = max(f[j+b[i]], f[j] + a[i]);
			}
		}

	if(f[100 * 10 * 100] == 0) puts("-1");
	else printf("%d\n", f[100 * 10 * 100]);

	return 0;
}

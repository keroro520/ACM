/*
	博弈  Nim变形  好题
	题意：有 n(1≤n≤1000) 堆石子，每堆石子数量为 1 到 1,000,000,000 之间的一个整数。两人玩游戏。每回合，游戏者必须从某堆中取走至少一个石子，取走最后一个石子的人获胜。问先手第一步有多少种走法使得他/她获胜


	思路：先算出所有石子的抑或和sum。sum^ai就得到除了第i堆石子外其它堆的抑或和，根据Nim的性质可知，要想由当前状态变到必败态，则(sum^ai)^bi==0，其中bi是从第i堆取出一部分石子之后剩余的石子。
		  也就是说sum^ai == bi
		  看到上面的式子，不难得出结论：在 Ai 中取走 Ai-(sum^Ai) 个石子是第一步在 Ai 中取石子的唯一获胜方式，当然前提是：
		  　　　　Ai ≥ (sum ^ Ai)
		  于是利用上面的结论对每一堆石子判断一下即可


		  我们可以借助上诉的方法证明，对于S(p1,p2...pn, p1^p2^...pn != 0)一定存在一种取法S->S'，使得S'(p1'^p2'^...^pn' == 0)
*/
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int n;
int a[1005];

int main()
{
	while(scanf("%d", &n) , n) {
		int sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			sum ^= a[i];
		}
		int ans = 0;
		for(int i = 0; i < n; i++)
			if(a[i] >= (sum ^ a[i])) ans++;
		if(sum == 0) ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}

/*
	思路题
	题意：要给一排长度为n的小球染色，第i个小球染上ci颜色。每次操作可以任选一段连续的长度恰好为K的区间染同一种颜色，问最少要多少次操作才能把所有小球染上相应的颜色，不可能的话输出-1.

	思路：死活想不出来，被wuyiqi GG瞬秒了。
		  
		  因为选的区间是固定的，所以同种颜色不相邻的小球不可能同一次染色。如果一个长度至少为K的区间都没有，则-1；否则，对于一个相邻小球不同颜色就染色，同色区间大于等于K的也染色。
		  我只能证明这样的染色方法是最小次数，但不能证明这方法是可行解。
		  “同种颜色不相邻的小球不可能同一次染色”，所以，遇到相邻的不同颜色小球当然至少要染一次色，即用我们的方法来染色是次数下限。

		  到底人家是怎么想的啊啊啊啊啊？我想不出来。。。233
*/
#include <stdio.h>
int n, K;
char str[20005];
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &K);
		scanf("%s", str);
		int sum = 0, ans = 0, flag = 0;
		for(int i = 0; i < n; i++) {
			if(sum < K && (!i || str[i] == str[i-1])) {
				sum++;
			} else ans++, sum = 1;
			if(sum == K) flag = true;
		}
		ans++;
		if(!flag) puts("-1");
		else 	  printf("%d\n", ans);
	}
	return 0;
}

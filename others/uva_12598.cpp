/*
	二分三分
	题意：有n个人排成一列，给出前k个人的数字，从第k+1个人开始，给他们分配数字，分配的方法是取当前没有出现过的最小正整数，例如8人，前3人的数字为3 5 8，第4到第8个人的数字分别为1 2 4 6 7，整个序列为3 5 8 1 2 4 6 7

	数据很大，不可能模拟
	1.留意到一点，因为是取最小的没用过的正整数，所以我们可以先把所有可能用的正整数保存下来，按区间保存
	2.例如已经用了3 5 8，没用的就是
	[1,2] 2个
	[4,4] 1个
	[6,8] 3个
	现在
	要为第k+1个人分配数字，那么可以立刻知道是分配1，因为1是第1个没有用过的
	要为第k+5个人分配数字，可以立刻知道是7，因为7是第5个没有用过的数字
	所以要为第m个数字分配数字，在上面没有用过的数字表里面找，先找到它在哪一块，再找到是哪一块的第几个，其中找在哪一块，用二分即可

	以上皆为摘抄
*/
//uva 12598
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXK		50005
int space[MAXK], a[MAXK], b[MAXK], n, K;
int  solve(int x)
{
	int l = 1, r = K + 1, ans = 0, mid ;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(space[mid] >= x) r = mid - 1, ans = mid;
		else    	   	    l = mid + 1;
	}
	ans = x - space[ans-1] + a[ans-1];
	return ans;
}
int main()
{
	int query, cases, Cas = 0, x;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d %d", &n, &K, &query);
		for(int i = 1; i <= K; i++) scanf("%d", &a[i]);
		memcpy(b, a, sizeof(int) * (K+1));
		sort(a+1, a+K+1);
		space[0] = a[0] = 0;
		space[K+1] = n - K;
		for(int i = 1; i <= K; i++)
			if(a[i] == a[i-1] + 1) space[i] = space[i-1];
			else			       space[i] = space[i-1] + a[i] - a[i-1] - 1;
		printf("Case %d:\n", ++Cas);
		while(query--) {
			scanf("%d", &x);
			if(x <= K) printf("%d\n", b[x]);
			else 	   printf("%d\n", solve(x-K));
		}
	}
	return 0;
}

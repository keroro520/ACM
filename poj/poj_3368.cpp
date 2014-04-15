/*
	RMQ   线段树
	题意：给出非递减序列{A}，若干询问区间[l,r]里出现最多的数。

	思路：要是线段树的话那就是水题。这里用RMQ的Sparse Table写。思路还是看别人的。感觉还是挺不错的思路 。
		  把原数列转化一下。。。
		       if (num2[i] == num2[i-1]) num[i] = num[i-1]+1;
	           else num[i] = 1;
	  	  然后对查询区间[l,r]分两部分，前面被切割部分和后面完整部分，前面直接计数，后面完整部分RMQ求最大值
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define			MAXN		100005
int a[MAXN], num[MAXN], st[MAXN][23], n;
void init()
{
	a[0] = -99999999;
	memset(st, 0, sizeof(st));
}
int Query(int l, int r)
{
	if(l > r) return 0;
	int k = (int)(log((r - l + 1) * 1.0)/log(2.0));
	return max(st[l][k], st[r-(1<<k)+1][k]);
}
int main()
{
	int query, l , r;
	while(scanf("%d%d", &n, &query) , n) {
		init();
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			if(a[i] == a[i-1]) num[i] = num[i-1] + 1;
			else num[i] = 1;
		}
		for(int i = 1; i <= n; i++) st[i][0] = num[i];
		for(int j = 1; (1 << j) <= n; j++)
			for(int i = 1; i + (1 << j) - 1 <= n; i++)
				st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
		while(query--) {
			scanf("%d%d", &l, &r);
			int tmp = l;
			while(a[l] == a[l-1] && l <= r) l++;
			printf("%d\n", max(Query(l, r), l - tmp));
		}
	}
	return 0;
}

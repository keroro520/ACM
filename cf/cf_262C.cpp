/*
	贪心
	题意：商场有若干个打折活动。
		  活动i：买qi件物品，可任意挑选额外的0-2件物品，但要求额外挑的这0-2件物品价钱不能超过买的那qi件物品的最低价钱(each of them mustn't be more expensive than the cheapest item out of the qi items in the cart.)
		  每个活动可以多次参加
		  Maxim要买n件物品，价钱分别为ai
		  问Maxim买这n件物品最少花多少钱


	思路：ai按大到小排序
		  从大到小开始买，买够Q件就拿额外的两件
		  其中Q为qi的最小值

		  证明略，只是YY了一下觉得Q=min{qi}是正确的就写上了
*/
#include <functional>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define			MAXN		100005
int a[MAXN], q[MAXN];
int n, m;
int main()
{
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) scanf("%d", &q[i]);
	sort(q+1, q+m+1);
	int tmp = q[1];
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a+1, a+1+n, greater<int>() );

	int i = 1, ans = 0;
	while(i <= n) {
		for(int j = 0; j < tmp && i <= n; j++, i++)
			ans += a[i];
		if(i > n) break;
		i += 2;
	}
	printf("%d\n", ans);
	return 0;
}

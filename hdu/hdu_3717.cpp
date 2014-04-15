/*
	二分判定  数学
	题意：n个石头从左到右排成一列，生命值ai。你可以在某一石头i的右边释放一个攻击力为p的技能，该技能对于所有{j | j <= i, p >= (i-j)^2 } 有p - (i-j)^2的伤害。任何石头当对其伤害累积到大于ai则该石头就死掉。但石头死掉并不代表它消失，也就是说，它还是在原来位置，整个石头序列不变。你有K个技能，你的目标是算出最小的p，使得用这K个技能就能够杀死所有石头。注意，所有技能的攻击力都得是p。

	思路：二分部分想到了，判定部分暴力搞TLE，得数学方法 + 队列搞，看了很久不理解。。不过应该也是化公式之类的，
		  判定部分是好题
		  判定部分抄别人的。
		  维护三个量，s,  队列里面所有x的∑(x-(i+1))
		  			  dis, 队列里面所有x的∑(x-i)^2
					  qsize, 队列里面x的个数，也就是能到达当前石头的技能。
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#define			inf			(1LL << 62)
#define			MAXN		50005
typedef		long long		ll;
int a[MAXN], Q[100005];
int n, K;
inline		ll		SQR(int x)		{ return (ll)x * x; } 
bool check(ll p)
{
	ll dis = 0;
	int j = n, car = 0, s = 0, cdr = 0, qsize = 0;
	do {
		while(cdr < car && SQR(Q[cdr] - j) >= p) {
			qsize --;
			dis -= p - SQR(Q[cdr] - (j+1)) ;
			s   -= (Q[cdr] - (j+1));
			cdr++;
		}
		
		dis -= qsize + 2 * s;
		s   += qsize;

		while(dis <= a[j]) {
			Q[car++] = j;
			dis += p;
			qsize++;
		}

		j--;
	} while(car <= K && 1 <= j);
	return j <= 0 && car <= K;
}
ll solve()
{
	ll l = 1, r = inf, ans, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &K);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		ll ans = solve();
		printf("%I64d\n", ans);
	}
	return 0;
}

/*
	数学 推规律 二分
	08哈尔滨acm现场赛A题

	记一下公式吧：a1 = 1, an = a(n-1) + n         //1 3 6 10 15 ...
	sum[n] = Σai
		      i(i+1)(i+2)
		   =  -----------
			       6
*/
#include <stdio.h>
typedef		long long 		ll;
#define		MID(l,r)		(((l) + (r)) >> 1)
ll Find1(ll x)
{
	ll l = 0, r = 5000000, ans = 0, mid;
	while(l <= r) {
		mid = MID(l, r);
		ll res = mid * (mid+1) / 2 * (mid + 2) / 3 ;
		if(res < 0 || x <= res) r = mid - 1;
		else ans = mid, l = mid + 1;
	}
	return ans ;
}
ll Find2(ll x)
{
	ll l = 0, r = 5000000, ans = 0, mid ;
	while(l <= r) {
		mid = MID(l, r);
		ll res = ( mid * (mid + 1) ) >> 1LL;
		if(res < 0 || x <= res) r = mid - 1;
		else ans = mid, l = mid + 1;
	}
	return ans;
}
int main()
{
	int cases;    ll x;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d", &x);
		ll heap = Find1(x);
		x -= heap * (heap+1) * (heap+2) / 6;
		ll row  = Find2(x);
		x -= row * (row+1) / 2;
		ll col = x;
		printf("%I64d %I64d %I64d\n", heap+1, row+1, col);
	}
	return 0;
}

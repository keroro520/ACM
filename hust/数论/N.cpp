/*
	组合数学 多项式定理
	(n, k1+k2+...+km) = n!/(k1!k2!...km!)

	m = 2时就是二项式定理

	http://baike.baidu.com/link?url=I7kMpX9cGpo7e9wlNG_5gOvDO5FSTk6UGIbIl82ST4cvmpdMS0qrLXLxtHoYSExf
*/
#include <stdio.h>
typedef		long long ll;
ll fac[15];
void init_fac()
{
	fac[0] = 1;
	for(ll i = 1; i < 13; i++) fac[i] = fac[i-1] * i;
}
int main()
{
	ll n, k; int x;
	init_fac();
	while(scanf("%lld %lld", &n, &k) != EOF) {
		ll tot = 1;
		while(k--) {
			scanf("%d", &x);
			tot *= fac[x];
		}
		printf("%lld\n", fac[n] / tot);
	}
	return 0;
}

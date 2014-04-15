/*
	数论  好题
	题意：要求输出n^k的前3位和后3位(数据保证答案不少于6位数字)

	思路：两数乘法的后三位自然是由各自后三位决定的，因此对于后三位我们完全可以用快速幂取模来做，但前三位就不行了。

	    但对于n^k我们可以做变形10^(k*logn)，这样又由于10^x只是改变小数点的位置我们自然就不用去考虑了，因此前3位只取决于10^(2+fmod(k*logn,1))，当输入最后结果的时候，由于要的是精确的前3位，所以应用强制转型忽略掉小数位，而不能直接用%.0f输出。


		我一开始前后3位都是仅保留后4位来搞快速幂，WA了，还是不明白为何会WA。
*/
//uva 11029
#include <stdio.h>
#include <math.h>
#define		SIZE		10000
typedef		long long ll;
ll SQR(ll x) { return x * x; }
ll trail_pow(ll x, ll k)
{
	if(k == 0) return 1;
	else if(k & 1) {
		ll res = trail_pow(x, k >> 1);
		res = ( SQR((res % SIZE)) % SIZE * x ) % SIZE;
		return res;
	} else {
		ll res = trail_pow(x, k >> 1);
		return SQR((res % SIZE)) % SIZE;
	}
}
ll leading_pow(ll x, ll k)
{
	if(k == 0) return 1;
	else if(k & 1LL) {
		ll res = leading_pow(x, k >> 1);
		while(res > SIZE) res /= 10;
		res = res * res ;
		while(res > SIZE) res /= 10;
		res *= x;
		while(res > SIZE) res /= 10;
		return res;
	} else {
		ll res = leading_pow(x, k >> 1);
		while(res > SIZE) res /= 10;
		res = res * res ;
		while(res > SIZE) res /= 10;
		return res;
	}
}
int main()
{
	ll n, k; int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lld %lld", &n, &k);

		double y =  log((double)n) / log(10.0);
		y *= k;
		double z = y - (int)y;
		double fuck = pow(10.0, 2+z);
		ll fuck2 = (ll)fuck;
		printf("%lld...", fuck2 % 1000);

		ll x = n % SIZE;
		ll res = trail_pow( x , k );
		printf("%03lld\n", res%1000);
	}
	return 0;
}

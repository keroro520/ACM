/*
	组合数学
	计算C(p,q) / C(r,s)

	思路：一开始怕直接计算会不会精度跪掉，想可能有公式，翻了一下别人的代码发现都是暴搞的，然后暴搞了一下就AC了
		  
		  计算的时候还是用fubao之前说的“一端大一端小，往里靠拢法”
*/
#include <stdio.h>
typedef		long long 	ll;

double calc(ll p, ll q, ll r, ll s)
{
	double t = 1;
	if(p - q < q) q = p - q;      
	if(r - s < s) s = r - s;
	ll i = 1, i_ = p, j = 1, j_ = r;		//i是小的一端，i_是大的一端
	while(i <= q || j <= s) {
		if(i <= q) {
			t = t * i_ / i;
			i_ --, i++;
		}
		if(j <= s) {
			t = t * j / j_;
			j_ --, j++;
		}
	}
	return t;
}
int main()
{
	ll p, q, s, r;
	while(scanf("%lld %lld %lld %lld", &p, &q, &r, &s) != EOF) {
		printf("%.5lf\n", calc(p, q, r, s));
	}
	return 0;
}

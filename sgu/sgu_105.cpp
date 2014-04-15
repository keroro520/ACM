//简单题，问序列1, 12, 123, ..., 12345678910, 12234567891011 ... ，前N项有多少项是能够被3整除的
#include <stdio.h>
typedef		long long		ll;
ll n;

int main()
{
	scanf("%I64d", &n);
	ll ans = 0;
	ans += n/3 * 2 ;
	if(n % 3) ans += n % 3 - 1;
	printf("%I64d\n", ans);
	return 0;
}

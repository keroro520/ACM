// 用简单的扩展欧几里得搞过了...
// 显而易见，若x mod k != 0，则x , x/k , x/k+1 两两互质，也就是说GCD(x/k, x/k+1) == 1，1 | x，所以可以用扩展欧几里得搞
#include <stdio.h>
typedef 	long long 	ll;
void EGCD(ll a, ll b, ll &x, ll &y) 
{
	if(b == 0) {
		x = 1, y = 0;
		return ;
	}
	EGCD(b, a%b, x, y);
	ll t = x;  x = y, y = t - a/b*y;
}
int main()
{
	int cases;  ll n, k;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lld %lld", &n, &k);
		if(n % k == 0) {
			printf("%lld %lld\n", 0, k);
			continue;
		}
		ll a = n/k, b = n/k+1, x, y;
		EGCD(a, b, x, y);
		x *= n;  y *= n;
		printf("%lld %lld\n", x, y);
	}
	return 0;
}

#include <stdio.h>
#include <math.h>
typedef		long long ll;
inline	int 	SQR(int x) { return x * x; }
ll hello(int x, int base)
{
	ll ans = 0;
	while(x) {
		ans += SQR(x % base);
		x /= base;
	}
	return ans;
}
ll calc(int n, int base)
{
	if(n == 1) return 1;
	ll ans = 1;
	ans += hello(n, base);
	for(int i = 2, oo = (int) sqrt(n+0.5); i <= oo; i++) if(n % i == 0) {
		ans += hello(i, base); //printf("%d ", i);
		if(n / i != i) ans += hello(n/i, base); //printf("%d ", n/i);
	}
	return ans;
}
void output(ll x, int base)
{
	if(x == 0) return ;
	output(x / base, base);
	if(x % base > 9) printf("%c", 'A'+x%base-10);		//
	else printf("%d", x % base);
}
int main()
{
	int n, base;
	while(scanf("%d %d", &n, &base) != EOF) {
		ll ans = calc( n, base);
		output(ans, base);
		puts("");
	}
	return 0;
}

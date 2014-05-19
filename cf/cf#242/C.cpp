/*
	数学

	列了一下就会发现
	Q'  = p1 ^ p2 ^ .. ^ pn
	Q'' = (1 mod 1) ^ (1 mod 2) ^ .. ^ (1 mod n) ^
		  (2 mod 1) ^ (2 mod 2) ^ .. ^ (2 mod n) ^
		  ...
		  (n mod 1) ^ (n mod 2) ^ .. ^ (n mod n)

  变换下= (1 mod 1) ^ (2 mod 1) ^ .. ^ (n mod 1) ^
  		  (1 mod 2) ^ (2 mod 2) ^ .. ^ (n mod 2) ^
		  ...
		  (1 mod n) ^ (2 mod n) ^ .. ^ (n mod n)
	发现循环节了吧, 以2*i为长的循环节, 再乱搞搞就成了
*/
#include <stdio.h>
typedef		long long		ll;
ll f[1000005];
int main()
{
	ll n, ans = 0, x;
	scanf("%I64d", &n);
	for(int i = 0; i < n; i++) scanf("%I64d", &x), ans ^= x;

	f[0] = 0;
	for(ll i = 1; i <= n; i++) f[i] = f[i-1] ^ i;
	for(ll i = 2; i <= n; i++) {
		x = n % (i * 2);
		if (x > i) ans ^= f[i-1] ^ f[x-i];
		else if (x == i) ans ^= f[i-1];
		else ans ^= f[x];
	}
	printf("%I64d\n", ans);
	return 0;
}

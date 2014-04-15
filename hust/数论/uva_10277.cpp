/*
	数论   概率   叫什么唯一分解定理?
	题意：给p,q，表示概率p/q。 有n双红袜子，m双黑袜子，从这m+n双袜子里取出两双，两双都是红袜子的概率为p/q，求满足条件的最小n和m，不存在输出impossible（袜子总数最多为50000）

	思路：记N = n+m。
		  首先对p/q进行化简，可得到p / q = n*(n-1) / (N*(N-1))
		  ==> p * N * (N-1) = q * n * (n-1)            
		  因为p,q互质，所以q | N*(N-1), p | n*(n-1)
		  然后这个时候就可以枚举N，搞出n，判断一下~~

		  知道思路就挺简单了....虽说思路也挺简单的，话说为什么我卡了两天？？？！！我是大沙茶...
*/
//uva 10277
#include <stdio.h>
#include <math.h>
typedef		long long 	ll;

ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a%b) ; }
int main()
{
	ll p, q;
	while( scanf("%lld %lld", &p, &q) , p || q ) {
		if(p == 0) { puts("0 2"); continue; }

		ll d = GCD(p, q), N = 2;
		p /= d, q /= d;

		for(N = 2; N <= 50000; N++) if( N*(N-1) % q == 0 ) {
			ll x = N*(N-1) / q * p;
			ll n = (ll) sqrt(x + 0.5) ;
			if(n*(n+1) == x) {
				n++;
				printf("%lld %lld\n", n, N-n);
				break;
			}
		}
		if(N > 50000) puts("impossible");
	}
	return 0;
}

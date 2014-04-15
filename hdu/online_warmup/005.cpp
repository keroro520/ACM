#include <algorithm>
#include <stdio.h>
using namespace std;
#define			MAXN		100005
long long Sum[MAXN], f[MAXN];
long long n, A, B;
long long calc(long long n)
{
	long long sum = 0;
	for(int i = 0; i < n; i++) sum += abs(i%A - i%B);
	return sum;
}
long long gcd(long long a, long long b)
{
	return b == 0 ? a : gcd(b, a%b);
}
long long lcm(long long a, long long b)
{
	return a/gcd(a,b) * b;	
}
void init()
{
	for(int i = 1; i <= 100000; i++) f[i] = f[i-1] * 2 + i;
	for(int i = 1; i <= 100000; i++) Sum[i] = Sum[i-1] + i;
}
int main()
{	
	int cases;
	init();
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d%I64d%I64d", &n, &A, &B);
		if(A > B) swap(A, B);
		long long l = lcm(A, B), ans;
		
		if(B % A == 0) ans = Sum[B/A-1] * A * A;
		else if(n & 1LL) ans = (Sum[A] + A) * (B - A)  +    (f[A] - Sum[A] + Sum[A/2]) * 2 - Sum[A/2]*2;
		else ans = (Sum[A] + A) * (B - A ) +      f[A-1] * 2 ;
		
		
		n = 50;
		for(long long i = 0; i <= n; i++) printf("%lld  %lld  %lld  %lld\n", i, i%A, i%B, abs( i%A - i%B));



		//ans = n/l * ans + calc(n-n/l*l);
		printf("%I64d\n", ans);
	}
	return 0;
}

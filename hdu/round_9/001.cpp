#include <stdio.h>
#define     MOD     1000000007LL

long long SQR(long long x) {
    return x * x % MOD;
}
long long calc(long long q, long long n)
{
    if(!n) return 1;
    if(n & 1LL) return (q * calc(q, n-1)) % MOD;
    else return SQR(calc(q, n/2 ));
}
int main()
{
    long long n, A0, AX, AY, B0, BX, BY;
//    while(scanf("%lld", &n) != EOF) {
//        scanf("%lld%lld%lld", &A0, &AX, &AY);
//        scanf("%lld%lld%lld", &B0, &BX, &BY);
//    }
}

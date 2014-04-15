#include <stdio.h>
#define     MOD     1000000007LL
long long A[1000], B[1000];
long long A0, AX, AY;
long long B0, BX, BY;
int n;
int main()
{
    while(scanf("%d", &n) != EOF) {
        scanf("%lld%lld%lld", &A0, &AX, &AY);
        scanf("%lld%lld%lld", &B0, &BX, &BY);
        printf("%lld   %lld   %lld\n", A0, 
        A[0] = A0, B[0] = B0;
        for(int i = 1 ; i < n-1; i++) {
            A[i] = (A[i-1]*AX + AY) % MOD;
            B[i] = (B[i-1]*BX + BY) % MOD;
        }
        long long sum = 0;
        for(int i = 0; i < n-1; i++) {
            sum = (sum + A[i] * B[i]) % MOD;
        }
        printf("%lld\n", sum);
    }
    return 0;
}

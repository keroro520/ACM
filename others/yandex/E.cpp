#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    100005
long long n, X, K;
long long a[MAXN], sum[MAXN];

bool cmp(long long a, long long b) { return a > b; }
int main()
{
    scanf("%lld%lld%lld", &n, &X, &K);
    
    long long tmp = K + X;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        ans += a[i] / tmp;
        a[i] %= tmp;
    }
    sort(a, a+n, cmp);
    long long rest = 0;
    for(int i = n-1; i >= 0; i--) {
        sum[i] = sum[i+1] + a[i];
    }
    for(int i = 0; i < n; i++) {
        if(rest >= sum[i]) break;
        if(a[i] > X) rest += K+X - a[i];
        else rest += K;
        ans++;
    }
    printf("%lld\n", ans);
    return 0;
}

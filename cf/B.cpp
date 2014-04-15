#include <stdio.h>
#include <limits.h>
#include <algorithm>
using namespace std;
#define     MAXN    200005
int n, K;
int a[MAXN], pos[MAXN];
long long f[MAXN], g[MAXN], sum[MAXN];
int main()
{
    scanf("%d%d", &n, &K);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i];
    pos[K-1] = 1;
    for(int i = K; i <= n; i++) {
        if(f[i-1] >= sum[i] - sum[i-K]) {
            f[i] = f[i-1];
            pos[i] = pos[i-1];
        } else {
            f[i] = sum[i] - sum[i-K];
            pos[i] = i - K + 1;
        }
    }
    for(int i = K; i <= n; i++) g[i] = f[i-K] + sum[i] - sum[i-K];
    long long ans = (INT_MIN);
    int ansi, ansj;
    for(int i = 2*K; i <= n; i++) 
        if(ans < g[i]) {
            ans = g[i];
            ansi = pos[i - K];
            ansj = i - K + 1;
        }
    printf("%d %d\n", ansi, ansj);
    return 0;
}

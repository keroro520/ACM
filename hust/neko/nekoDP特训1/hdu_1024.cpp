/*
    最大m段子段和   DP   好题

    http://blog.acmol.com/%E3%80%90hdu-1024%E3%80%91-max-sum-plus-plus.acmol
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN        1000010
#define     INF         999999999999
int n, m, a[MAXN];
long long f[MAXN], g[MAXN];
int main()
{
    while(scanf("%d%d", &m, &n) != EOF) {
        for(int i = 0; i < n; i++) scanf("%d\n", a+i);
        for(int i = 1; i <= m; i++) 
            f[i] = g[i] = -INF;
        
        for(int i = 0; i < n; i++)
            for(int j = m; j > 0; j--) {
                f[j] = max(f[j], g[j-1]) + a[i];
                g[j] = max(g[j], f[j]);
            }
        printf("%I64d\n", g[m]);
    }
    return 0;
}

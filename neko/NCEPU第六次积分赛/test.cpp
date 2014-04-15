#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
using namespace std;
#define     MAXN    10005

const int Bit[64] = {1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 } ;
int a[MAXN], sum[2][MAXN], f[MAXN][64], g[MAXN][64];
int n;
int Query(int l1, int r1, int l2, int r2)
{
    int j1 = (int)(log2(r1-l1+1));
    int j2 = (int)(log2(r2-l2+1));
    return max(f[l2][j2], f[r2-Bit[j2]+1][j2]) + max(g[l1][j1], g[r1-Bit[j1]+1][j1]);
} 
int main()
{
    int cases, query, x1,x2,y1,y2;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        sum[0][0] = a[0];
        for(int i = 1; i < n; i++) sum[0][i] = sum[0][i-1] + a[i];
        sum[1][n-1] = a[n-1];
        for(int i = n-2; i >= 0; i--) sum[1][i] = sum[1][i+1] + a[i];
        for(int i = 0; i < n; i++) {
            f[i][0] = sum[0][i];
            g[i][0] = sum[1][i];
        }
        for(int j = 1; Bit[j] < n; j++)
            for(int i = 0; i + Bit[j] - 1 < n; i++) {
                f[i][j] = max(f[i][j-1], f[i+Bit[j-1]][j-1]);
                g[i][j] = max(g[i][j-1], g[i+Bit[j-1]][j-1]);
            }
        scanf("%d", &query);
        while(query--) {
            long long t = 0;
            scanf("%d%d", &x1, &y1);
            scanf("%d%d", &x2, &y2);
            x1--, y1--;
            x2--, y2--;
            t += Query(x1,y1,x2,y2);
            t += -g[y1+1][0];    //
            t += -f[x2][0];
            t += sum[0][x2] - sum[0][y1];
            printf("%lld\n ", t);
        }
    }
}

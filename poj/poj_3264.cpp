/*
    RMQ  ST Sparse Table 简单题
*/
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    50005

const int Bit[64] = {1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 } ;
int a[MAXN], f[2][MAXN][64];
int n;

int Query(int left, int right)
{
    int j = (int)(log2(right-left+1));
    int a = min(f[0][left][j], f[0][right-Bit[j]+1][j]);
    int b = max(f[1][left][j], f[1][right-Bit[j]+1][j]);
    return b - a;
}
/*
int Set(int a, int x)           //动态修改元素              看起来貌似代价不小耶
{
    f[a][0] = x;
    for(int j = 1; Bit[j] <= n; j++)
        for(int i = max(x+1-Bit[j]) : 0; i < x && i + Bit[j] - 1 < n; i++)
            f[i][j] = cmp(f[i][j-1], f[i+Bit[j-1]][j-1]);
}
*/
int main()
{
    int query;
    scanf("%d%d", &n, &query);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i++) f[0][i][0] = f[1][i][0] = a[i];
    for(int j = 1; Bit[j] < n; j++)
        for(int i = 0; i + Bit[j]-1 < n; i++) {
            f[0][i][j] = min(f[0][i][j-1], f[0][i+Bit[j-1]][j-1]);
            f[1][i][j] = max(f[1][i][j-1], f[1][i+Bit[j-1]][j-1]);
        }
    while(query--) {
        int left, right;
        scanf("%d%d", &left, &right);
        printf("%d\n", Query(left-1, right-1));
    }
    return 0;
}

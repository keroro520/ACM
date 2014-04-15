/*
    有负数，所以初始化为无穷小，而不是0
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    1005
int n, m, a[MAXN][MAXN], f[MAXN][MAXN];
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++) scanf("%d", &a[i][j]);
        memset(f, 128, sizeof(f));
        f[1][0] = 0;        //这一步只是为了考虑f[1][1]方便而已，用不着初始f[i][0]都为0.
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++) {
                if(i-1 <= 0) f[i][j] = f[i][j-1] + a[i][j];
                else if(j-1 <= 0) f[i][j] = f[i-1][j] + a[i][j];
                else f[i][j] = max(f[i-1][j], f[i][j-1]) + a[i][j];
                
            }
        printf("%d\n", f[n][m]);
    }
    return 0;
}

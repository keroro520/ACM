#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define     MAXN    105
int a[MAXN][MAXN], f[MAXN][MAXN];
int n;
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        memset(f, 0, sizeof(f));
        for(int i = 1 ;i <= n; i++)
            for(int j = 1; j <= i; j++) scanf("%d", &a[i][j]);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= i; j++)
                f[i][j] = max(f[i-1][j-1], f[i-1][j]) + a[i][j];
        int ans = 0;
        for(int i = 1; i <= n; i++) ans = max(f[n][i], ans);
        printf("%d\n", ans);
    }
    return 0;
}


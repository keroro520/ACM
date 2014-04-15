/*
    DP  递归输出解
*/
//ural 1501
#include <stdio.h>
#include <string.h>
#define         ABS(x)      ((x) > 0 ? (x) : (-(x)))
#define         calc(x)     ((x) == 0 ?  (1) : (-1))
#define         MAXN        1005
int a[MAXN], b[MAXN], f[MAXN][MAXN];
int n;
inline char rdc() { scanf(" "); return getchar(); }
void output(int p, int q)
{
    if(p == 0 && q == 0) return ;
    if(p-1 >= 0 && f[p][q] == f[p-1][q] + calc(a[p])) {
        output(p-1, q);
        printf("1");
    } else {
        output(p, q-1);
        printf("2");
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) a[i] = rdc() - '0';
    for(int i = 1; i <= n; i++) b[i] = rdc() - '0';
    memset(f, 127, sizeof(f));
    printf("%d\n", f[0][0]);
    memset(f, 128, sizeof(f));
    f[0][0] = 0;
    for(int i = 1; i <= n; i++) { f[i][0] = f[i-1][0] + calc(a[i]); if(ABS(f[i][0]) > 1) f[i][0] = 9999999; }
    for(int i = 1; i <= n; i++) { f[0][i] = f[0][i-1] + calc(b[i]); if(ABS(f[0][i]) > 1) f[0][i] = 9999999; }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            int tmp = f[i-1][j] + calc(a[i]);
            if(ABS(tmp) <= 1) { f[i][j] = tmp; continue; }
            tmp = f[i][j-1] + calc(b[j]);
            if(ABS(tmp) <= 1) { f[i][j] = tmp; }
        }
    if(f[n][n] == 0) output(n,n);
    else printf("Impossible");
    printf("\n");
    return 0;
}

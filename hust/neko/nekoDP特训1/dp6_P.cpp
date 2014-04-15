#include <stdio.h>
#include <string.h>
#define     MAXN        2005
#define     MOD         1000000007
int f[MAXN][MAXN], g[MAXN][MAXN];
char A[MAXN], B[MAXN];

int main()
{
    scanf("%s%s", A+1, B+1);
    A[0] = '!', B[0] = '-';
    int n = strlen(A), m = strlen(B);
    for(int i = 0; i <= n; i++) g[i][0] = 1;
    for(int i = 0; i <= m; i++) g[0][i] = 1;
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++) {
            if(A[i] == B[j]) {
                f[i][j] = f[i-1][j-1] + 1;
                g[i][j] = g[i-1][j-1];
            } else if(f[i-1][j] == f[i][j-1]) {
                f[i][j] = f[i-1][j] ;
                g[i][j] = (g[i-1][j] + g[i][j-1]) % MOD;
            } else if(f[i-1][j] >  f[i][j-1]) {
                f[i][j] = f[i-1][j] ;
                g[i][j] = g[i-1][j];
            } else {
                f[i][j] = f[i][j-1] ;
                g[i][j] = g[i][j-1];
            }
    }

    printf("%d\n", g[n-1][m-1] % MOD);
    return 0;
}

/*
    TLE  WA
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    479
#define     MOD     1000000007
int n, m;
int a[MAXN][MAXN];
int f[2][MAXN][11][11][2];
int main()
{
    int cases, Cas = 1;
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d: ", Cas++);
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            getchar();
            for(int j = 1; j <= m; j++)
                a[i][j] = getchar() - '0';
        }

        memset(f, 0, sizeof(f));
        int sum = 0, cur = 0;
        for(int i = 1; i <= n; i++) {
            memset(f[cur], 0, sizeof(f)/2);
            for(int j = 1; j <= m; j++) {
                
                for(int k = 10; k > 10-a[i][j]; k--)    //h == 0
                    for(int s = 0; s <= 10; s++)
                        f[cur][j][0][s][1] = f[1-cur][j][k][s][0] + f[cur][j-1][k][s][0];
            
                for(int k = 10; k > 10-a[i][j]; k--)    //s == 0
                    for(int h = 0; h <= 10; h++)
                        f[cur][j][h][0][0] = f[1-cur][j][h][k][1] + f[cur][j-1][h][k][1];

                for(int h = 10; h >= a[i][j]; h--)
                    for(int s = 1; s <= 10; s++) {
                        f[cur][j][h][s][1] = f[1-cur][j][h-a[i][j]][s][0] + f[cur][j-1][h-a[i][j]][s][0];
                        if(f[cur][j][h][s][1] >= MOD) f[cur][j][h][s][1] %= MOD;
                    }
                for(int s = 10; s >= a[i][j]; s--)
                    for(int h = 1; h <= 10; h++) {
                        f[cur][j][h][s][0] = f[1-cur][j][h][s-a[i][j]][1] + f[cur][j-1][h][s-a[i][j]][1];
                        if(f[cur][j][h][s][0] >= MOD) f[cur][j][h][s][0] %= MOD;    //
                    }
                
                f[cur][j][a[i][j]][0][1]++;
                //f[i][j][0][a[i][j]][0]++;
                for(int h = 0; h <= 10; h++) sum += f[cur][j][h][h][0] + f[cur][j][h][h][1];
                sum %= MOD;
            }
            cur = 1 - cur;
        }
        printf("%d\n", sum);
    }
    return 0;                       
}   

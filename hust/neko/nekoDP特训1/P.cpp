/*
    样例都没用过。
    WA
*/
#include <stdio.h>
#include <string.h>
#define         MAXN    100005
#define         N       100000
double f[MAXN]; 
int  b[MAXN][300], yinzi[MAXN][300], cnt[MAXN], cnt2[MAXN];
void init()
{
    for(int i = 1; i <= N; i++) {
        int j = i+i;
        while(j <= N) {
            b[i][cnt[i]++] = j;
            yinzi[j][cnt2[j]++] = i;
            j += i;
        } 
    }
}
double DP(int n)
{
    memset(f, 0, sizeof(f));
    
    for(int i = 0; i < cnt2[n]; i++) {
        int x = yinzi[n][i];
        for(int j = 0; j < cnt[x]; j++) {
            int y = b[x][j];
            f[y] += f[x] + (1.0)/cnt[x];
        }
    }
    return f[n];
}

int main()
{
    int n, cases, Cas = 0;
    init();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        printf("%.10f\n", DP(n));
    }
    return 0;
}

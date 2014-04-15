/*
    简单区间DP
*/
//lightoj 1033
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define         MAXN            105
int n, f[MAXN][MAXN];
char S[MAXN];
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    S[0] = '-';
    while(cases--) {
        scanf("%s", S+1);
        n = strlen(S); 
        for(int j = 1; j < n; j++)
            for(int i = j; i > 0; i--)
                if(S[i] == S[j]) f[i][j] = f[i+1][j-1];
                else f[i][j] = 1 + min(f[i+1][j], f[i][j-1]);
        printf("Case %d: %d\n", ++Cas, f[1][n-1]);
    }
    return 0;
}

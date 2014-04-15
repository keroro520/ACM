/*
    区间DP  好题

    其实我也还没理解这道题跟回文有什么不用一样。


    正向其实可以看成j(区间右端)不断移动；逆向看成i(区间左端)不断移动。
    然后转移的时候就可以根据方向来搞了。
    
    注释掉的4条语句是逆向的想法。就是状态转移的时候i是从右往左。


    Quetion : 
             

*/
//lightoj 1422
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN        105
int a[MAXN], f[MAXN][MAXN], n;
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        
        for(int l = 1; l <= n; l++)
            //for(int i = n; i > 0; i--) {                //为什么要逆着？
            for(int i = 1; i + l - 1 <= n; i++) {
                int j = i + l - 1;
                f[i][j] = f[i][j-1] + 1;
//                f[i][j] = f[i+1][j] + 1;
//                for(int k = i; k <= j; k++)
                for(int k = i; k <= j; k++) 
                    if(a[k] == a[j]) f[i][j] = min(f[i][j], f[i][k] + f[k+1][j-1]);
                //    if(a[k] == a[i]) f[i][j] = min(f[i+1][k-1]+f[k][j], f[i][j]);       //TODO
            }
        printf("Case %d: %d\n", ++Cas, f[1][n]);
    }
    return 0;
}

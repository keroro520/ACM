/*
    区间DP预处理   好题

    题意：一步可以改变A串的一段为同一个字母，问用最少步数把A串变成B串。
    
    思路：代码里面细节用 //TODO  注释了

*/
//hdu 2476
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    105
char A[MAXN], B[MAXN];
int f[MAXN][MAXN], ans[MAXN];
int main()
{
    A[0] = B[0] = '-';
    while(scanf("%s%s", A+1, B+1) == 2) {
        int len = strlen(A);
        memset(f, 0, sizeof(f));
        for(int i = 1; i < len; i++)                //初始化简单，可以初始化为INF, 但千万不能用memset，因为后面对于i>j的情况需要等于0
            for(int j = i; j < len; j++)
                f[i][j] = j - i + 1;
        for(int l = 1; l < len; l++)
            for(int i = 1; i + l - 1< len; i++) {
                int j = i + l - 1;
                for(int k = i+1; k <= j; k++)   //TODO  k是小于等于j
                    if(B[i] == B[k])        //TODO      是用B串预处理
                        f[i][j] = min(f[i][j], f[i][k-1] + f[k+1][j]);
                    else f[i][j] = min(f[i][j], f[i+1][j] + 1);        //TODO 
            }
        memset(ans, 0, sizeof(ans));
        for(int i = 1; i < len; i++) {
            ans[i] = f[1][i];       //TODO
            if(A[i] == B[i]) ans[i] = ans[i-1];
            for(int k = 1; k < i; k++)
                ans[i] = min(ans[i], ans[k] + f[k+1][i]);
        }
        printf("%d\n", ans[len-1]);
    }
    return 0;
}

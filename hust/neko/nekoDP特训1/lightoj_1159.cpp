/*
    简单DP
    题意：3个串的最长公共字串的长度

    思路：稀里糊涂AC了 =_=
          多个串，多一维，f[i][j][k]...
*/
//lightoj 1159
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    51
int f[MAXN][MAXN][MAXN];
char A[MAXN], B[MAXN], C[MAXN];
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    A[0] = B[0] = C[0] = '-';
    while(cases--) {
        scanf("%s%s%s", A+1, B+1, C+1);
        int len_a = strlen(A), len_b = strlen(B), len_c = strlen(C);
        for(int i = 1; i < len_a; i++)
            for(int j = 1; j < len_b; j++)
                for(int k = 1; k < len_c; k++) {
                    int &x = f[i][j][k];
                    if(A[i] == B[j] && A[i] == C[k]) x = f[i-1][j-1][k-1] + 1;
                    else x = max(f[i-1][j][k], max(f[i][j-1][k], f[i][j][k-1]));
                }
        printf("Case %d: %d\n", ++Cas, f[len_a-1][len_b-1][len_c-1]);
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define         MAXN        1005
#define         MOD         1000007
int f[MAXN][MAXN], dlcs[MAXN][MAXN];
int snxt[256][MAXN], tnxt[256][MAXN];
char A[MAXN], B[MAXN];
int n, m, Index, longest;
void LCS()
{
    for(int i = 0; i <= n; i++) f[i][0] = 0;
    for(int i = 0; i <= m; i++) f[0][i] = 0;
    for(int i = 1; i < n; i++)
        for(int j = 1; j < m; j++) {
            if(A[i] == B[j]) f[i][j] = f[i-1][j-1] + 1;
            else f[i][j] = max(f[i-1][j], f[i][j-1]);
        }
    longest = f[n-1][m-1];
}
void Init()
{
    for(int ch = 'a'; ch <= 'z'; ch++) {
        int label = -1;
        for(int j = n-1; j >= 0; j--) {             //!!!TODO
            if(ch == A[j]) label = j;
            snxt[ch][j] = label;
        }
        label = -1;
        for(int j = m-1; j >= 0; j--) {
            if(ch == B[j]) label = j;
            tnxt[ch][j] = label;
        }
    }
}
int  Distinct(int i, int j)
{
    //if(i > 0 && j > 0 && (f[i][j] == longest || f[i-1][j-1] == longest)) return 1;
    if(f[i][j] == longest) return 1;
    if(i > n || j > m) return 0;
    if(dlcs[i][j] != -1) return dlcs[i][j];
    dlcs[i][j] = 0;
    for(char ch = 'a'; ch <= 'z'; ch++) {
        int  is = snxt[ch][i];
        int  it = tnxt[ch][j];
        
        if(is < 0 || it < 0) continue;

        if(f[is+1][it+1] == f[i][j] + 1) {   
            dlcs[i][j] += Distinct(is+1, it+1);
            dlcs[i][j] %= MOD;
        }
    }
    return dlcs[i][j];
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    A[0] = B[0] = '-';
    while(cases--) {
        scanf("%s%s", A+1, B+1);
        n = strlen(A), m = strlen(B);
        LCS();
        Init();
        memset(dlcs, -1, sizeof(dlcs));
        Distinct(0, 0);
        printf("Case %d: %d\n", ++Cas, max(1, dlcs[0][0]));
    }
    return 0;
}

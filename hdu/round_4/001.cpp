#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
using namespace std;
#define     MAXN    1005
#define     MOD     10007
string s;
int f[MAXN][MAXN];
void init()
{
    memset(f, 0, sizeof(f));
    for(int len = s.length(), i = 0; i < len; i++) f[i][i] = 1;
}
void solve(int n)
{
    for(int j = 0; j < n; j++)
        for(int i = j-1; i >= 0; i--) {
            if(s[i] == s[j]) f[i][j] = (f[i+1][j] + f[i][j-1] + 1) % MOD;
            else f[i][j] = (f[i+1][j] + f[i][j-1] - f[i+1][j-1] + MOD) % MOD;
        }
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        cin >> s;
        init();
        solve(s.length());
        printf("Case %d: %d\n", ++Cas, f[0][s.length()-1]);
    }
    return 0;
}

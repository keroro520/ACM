/*
    区间DP  DP优化  预处理  好题
    题意：把字符串s拆成若干连续字串，要求这些连续字串都是回文串，问最少能够拆多少部分就满足条件了。

    思路：好题。朴素的思路是gyy的，预处理O(n^3)+状态转移方程O(n^2)，neko提供了预处理时用区间DP使得预处理降为O(n^2)，最后他在提供思路说我们可以在预处理的时候把“无用的子状态”剔除掉，对于dp[r]，所谓“有用的子状态”为[l,r]回文的l，使得状态转移方程那边又剪了很多东西。
*/  
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define     MAXN        1024
bool pal[MAXN][MAXN];       //判断[l,r]是否为回文。
int f[MAXN];
vector<int> pre[MAXN];      //若[l,r]是回文，这pre[r].push_back(l)，这是为了状态转移的时候减少无用子状态数，所以在预处理的时候搞出来
char s[1024];

void init(int n)
{
    memset(pal, true, sizeof(pal));
    for(int i = 0; i < n; i++) pre[i].clear();
    for(int j = 0; j < n; j++)
        for(int i = j; i >= 0; i--)
            if(s[i] == s[j] && pal[i+1][j-1]) pre[j].push_back(i);
            else pal[i][j] = false;
}
int calc(int n)
{
    memset(f, 127, sizeof(f));
    f[0] = 1;
    for(int v = 1; v < n; v++) {
        for(int Size = pre[v].size(), i = 0; i < Size; i++) {
            int u = pre[v][i];
            if(u == 0) f[v] = min(f[v], 1);
            else f[v] = min(f[v], f[u-1]+1);
        }
    }
    return f[n-1];
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%s", s);
        init(strlen(s));
        printf("Case %d: %d\n", ++Cas, calc(strlen(s)));
    }
    return 0;
}

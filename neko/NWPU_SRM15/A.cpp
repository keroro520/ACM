/*
    记忆化搜索   多维搜索       启发题

    题意：m个气球n个人吹。第i个人一分钟能吹Ai个气球然后至少休息Bi分钟才能吹下一分钟。问最少需要多少分钟吹完所有气球？(Bi <= 4)

    思路：f[sum][a1][a2][a3][a4]表示吹sum个气球，前1,2,3,4分钟吹的人分别是a1,a2,a3,a4需要的最少时间。当题目中出现一维非常小时，此处往往就是问题的突破口。

    完全就是按雷神的代码来写的：http://www.cnblogs.com/jianglangcaijin/archive/2013/01/26/2877731.html



    启发：虽然知道Bi<=4是突破口，但自己想的时候也没有什么好的搜索方法。。想过f[i][j]表示第i个气球让志愿者j吹，但是搜起来的话要处理的细节搞不清楚，就写不下去。

          说说这道题的记忆化搜解法的启发吧。
          平常真的对多维的东西不太敢想，以至于就算AC了也觉得，下次再遇到这种题，还是会跪。因为没能把题目和该算法联系起来。好像知道“其所以然”...
*/
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug   printf("!\n")
#define     MAXM    102
#define     MAXN    12
#define     INF     999999999
int f[MAXM][MAXN][MAXN][MAXN][MAXN];
int rest[MAXN], work[MAXN];
int M, n;
int dfs(int sum, int a, int b, int c, int d) ;
int main()
{
    scanf("%d%d", &M, &n);
    for(int i  = 1; i <= n; i++) {
        scanf("%d%d", &work[i], &rest[i]);
    }
    memset(f, -1, sizeof(f));
    printf("%d\n", dfs(M, 0, 0, 0, 0));
    return 0;
}
int dfs(int sum, int a, int b, int c, int d)
{
    if(sum <= 0) return 0;
    int &result = f[sum][a][b][c][d];
    if(result != -1) return result;
    result = INF;   
    result = min(result, 1 + dfs(sum, 0, a, b, c));//
    for(int i = 1; i <= n; i++) if(work[i]) {
        if(i == a && rest[i] > 0) continue;
        if(i == b && rest[i] > 1) continue;
        if(i == c && rest[i] > 2) continue;
        if(i == d && rest[i] > 3) continue;
        result = min(result, 1 + dfs(sum - work[i], i, a, b, c));
    }
    return result;
}

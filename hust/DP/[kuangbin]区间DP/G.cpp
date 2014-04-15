/*
    区间DP  好题

    题意：给定一个序列，序列内的人有屌丝值Di，是第然后将这个序列进栈，第i个人如果是第k个出栈，那么最后的屌丝总值增加Di * (k-1), 求一个出栈序列使得总屌丝值最小。

    思路：做完上一道hdu_2476区间DP，然后还是想要那个思路来做这道题，就先预处理出区间[i,j]顺序放和逆序放的区间总愤怒值，然后再开一个DP计算全局最优值。我的区间f[i,j]是相对于全局(即n个人)的愤怒值。
          然后，然后就跪了。因为计算的时候不知道怎么转移。

          正解的f[i,j]定义：[i,j]区间的最小花费，只考虑[i,j]区间，跟全局无关。
          这样定义，然后跟全局的关系在后面的DP计算时再考虑进去，这样思路就很明晰。
          假设区间[i,j]里，第i个人是第k个进场的，即在i+1之后的k-1个人率先进场，则
          区间[i,j]花费 = 在i号之前进场的([i+1 ~ i+1+k-1-1])  +  i号第k个进场  +  在i号之后进场的([k+1 ~ j])
                        = f[i+1, i+1+k-1-1] + D[i]*(k-i) + f[i+1, j] + (k-i+1)*({k+1..j}的ds脾气和)
    
          
          还是挺有收获的，我原来思考状态的定义时习惯考虑“搞完区间(i,j)的花费”，但是现在做了两题区间DP都是定义为“搞完区间[i,j]时全局的花费”，其实就等于“搞区间[i,j]之前的全局花费 + 搞区间[i,j]的全局花费增量”。
          之前YY出了个“局部独立性”...我觉得这个概念可以帮助思考dp状态以及状态转移，就是推测状态的定义时，最好满足“局部独立性”，不然转移时会比较麻烦。
*/
// hdu 4283
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    105
#define     INF     999999999
int sum[MAXN], f[MAXN][MAXN], d[MAXN];
int n;
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
        for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + d[i];
        for(int i = 1; i <= n; i++) {
            //f[i][i] = 0;
            //for(int j = i+1; j <= n; j++) f[i][j] = INF;
        }
        for(int l = 1; l <= n; l++)
            for(int i = 1; i + l - 1 <= n; i++) {
                int j = i + l - 1;
                f[i][j] = f[i][j-1] + d[j] * (j - 1);
                for(int k = i; k <= j; k++)
                    f[i][j] = min(f[i][j], f[i+1][k] + f[k+1][j] + d[i]*(k-i) + (k-i+1) * (sum[j]-sum[k]));
            }
        printf("Case #%d: %d\n", ++Cas, f[1][n]);
    }
    return 0;
}

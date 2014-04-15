/*
    概率DP
    题目：有2^n个队，相邻的两两打淘汰赛，求最后哪个队夺冠的概率最大。假设a1,a2,a3,..ak(i<k, ai<ak)为前一轮胜利的参赛者序列，则当前轮由a1,a2对手，a3,a4对手...

    思路：dp[i][j]表示第i轮时队j胜利，那么dp[i][j]前提就是i-1轮的时候j胜利，而且在第i轮赢了对手。
          那么接下来就是枚举j在第i轮时可能的对手k了，j要在i轮胜，就要在i轮把这些可能的对手k都打败。
          通过二进制发现规律，j与k的高位都相等，到了第i-1位刚好相反，就用这个性质判断是不是j在i轮的对手。
          dp[i][j] = Σ(dp[i-1][j] * dp[i-1][k] * p[j][k]),        (k >> (i-1) ^ 1) == (j >> (i-1))



    收获：原来这个规则下有这么个规律呀，j,k能在第i轮相遇的条件是(k >> (i-1) ^ 1) == (j >> (i-1)) !  “高位相同，i-1位相反”

    我看的题解：http://blog.csdn.net/acm_cxlove/article/details/7921608         几乎一模一样了=_=  数学白来搞概率伤不起呀
*/
//poj 3071
#include <stdio.h>
#define     N        8
#define     MAXN     (1 << N)
double p[MAXN][MAXN], f[N][MAXN];
int n;

int main()
{
    while(scanf("%d", &n), n != -1) {
        int top = (1 << n);
        for(int i = 0; i < top; i++)
            for(int j = 0; j < top; j++) scanf("%lf", &p[i][j]);

        for(int j = 0; j < top; j++) f[0][j] = 1;
        for(int i = 1; i <= n; i++)
            for(int j = 0; j < top; j++) {
                f[i][j] = 0;
                for(int k = 0; k < top; k++) if(((k >> (i-1)) ^ 1) == (j >> (i-1)) ) {      //TODO
                    f[i][j] += f[i-1][j] * f[i-1][k] * p[j][k];
                }
            }
         int index = 0;
         for(int j = 0; j < top; j++) if(f[n][j] > f[n][index]) index = j;
         printf("%d\n", index+1);
    }
    return 0;
}

/*
数位 DP

题意：问在n,m之间不含4和62序列（4和62为不吉利数, 62是连着的）的数字有多少个。

代码: solve(x) 应该是求[1, x)区间, 也就是1 ~ x-1  !!!
*/
#include <stdio.h>

int dp[10][3];
void init()
{
    dp[0][0] = 1;
    for(int i = 1; i <= 8; i++) {
        dp[i][0] = dp[i-1][0] * 9 - dp[i-1][1];
        dp[i][1] = dp[i-1][0];
        dp[i][2] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2]*10;
    }
}

int solve(int x)
{
    int sum = x;
    int len = 0;
    int bit[10];
    for(len = 0 ; x; x/=10) bit[++len] = x % 10;
    bit[len+1] = 0;     

    int ans = 0;
    bool flag = false;
    for(int i = len; i ; i--) {
        ans += dp[i-1][2] * bit[i];
        if(flag) {
            ans += dp[i-1][0] * bit[i];
        } else {
            if(bit[i] > 4) ans += dp[i-1][0];
            if(bit[i] > 6) ans += dp[i-1][1];
            if(bit[i+1] == 6 && bit[i] > 2) ans += dp[i][1];
        }
        if(bit[i] == 4 || (bit[i+1] == 6 && bit[i] == 2)) flag = true;
   }
   return sum - ans;    
}

int main()
{
    int l, r;
    init();
    while(scanf("%d%d", &l, &r), r&&l) {
        printf("%d\n", solve(r+1) - solve(l));
    }
    return 0;
}

/*
    DP 好题  简单题

    题意：给n个数，问有多少个连续的序列的和模M为0

    思路：对这种题有个结论：
          ***  对于i,j, i < j，如果sum[1..i] % M = sum[1..j] % M，则sum[i+1...j] % M = 0    ***

          我是觉得这个定理简单而巧妙~~
*/
//lightoj 1134
#include <stdio.h>
#include <string.h>
int cnt[100005];
int main()
{
    int cases, Cas = 0, n, MOD, x;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &MOD);
        memset(cnt, 0, sizeof(cnt));
        cnt[0] = 1;
        
        int sum = 0;
        long long ans = 0;
        while(n--) {
            scanf("%d", &x);
            sum = (sum + x) % MOD;
            ans += cnt[sum];
            cnt[sum]++;
        }
        printf("Case %d: %lld\n", ++Cas, ans);
    }
    return 0;
}

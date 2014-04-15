#include <stdio.h>
#define         MOD         1000000007
int ans, n;

void dfs(int sum, int start)
{
    if(sum == n) {
        ans ++;
        if(ans > MOD) ans -= MOD;
        return ;
    }
    if(n - sum < start) return ;
    for(int i = start; i <= n - sum; i++) {
        dfs(sum+i, i) ;
    }
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        ans = 0;
        for(int i = 1; i <= n; i++) dfs(i, i);
        printf("%d\n", ans);
    }
    return 0;
}

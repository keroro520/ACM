/*
    分组背包，还是比较裸的
    水濑

    唉，敲了好久分组背包还是WA，才取nocow上看了一下分组背包的伟代码，发现自己原来把第二和第三个循环倒了...
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     debug(x)   printf("!%d\n", x)
#define     MAXN    25
#define     MAXT    43210

int n, T;
int a[MAXN], sum[MAXN], f[MAXT];

int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &T);
        memset(f, 0, sizeof(f));
        int deadline;
        for(int i = 1; i <= n; i++) { 
            scanf("%d", &deadline);
            for(int j = 0; j < deadline; j++) scanf("%d", &a[j]);
            sum[0] = a[0];
            for(int j = 1; j < deadline; j++) sum[j] = sum[j-1] + a[j];
            for(int t = T; t >= 0; t--)
                for(int j = deadline-1; j >= 0; j--) if(t >= sum[j]){
                    f[t] = max(f[t], f[t-sum[j]] + j + 1);
                }
           
        }
        int ans = 0;
        for(int t = T; t >= 0; t--)
            ans = max(ans, f[t]);
        printf("%d\n", ans);
    }
    return 0;
}

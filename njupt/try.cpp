#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN    25
#define     MAXT    43210

int n, T;
int a[MAXN], sum[MAXN], f[2][MAXT];

int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &T);
        memset(f, 0, sizeof(f));
        int cur = 0, deadline;
        for(int i = 0; i < n; i++) {        //要不要初始化f[cur]?
            memset(f[cur], 0, sizeof(f)/2);
            scanf("%d", &deadline);
            for(int j = 0; j < deadline; j++) scanf("%d", &a[j]);
            sum[0] = a[0];
            for(int j = 1; j < deadline; j++) sum[j] = sum[j-1] + a[j];
            for(int j = deadline-1; j >= 0; j--)
                for(int t = T; t >= sum[j]; t--)
                    f[cur][t] = max(f[cur][t], f[1-cur][t - sum[j]] + j+1);
    
            cur = 1 - cur;
        }
        int ans = 0;
        for(int t = T; t >= 0; t--)
            ans = max(ans, f[1-cur][t]);
        printf("%d\n", ans);
    }
    return 0;
}

#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define         MAXN        100005
#define         MID(l,r)    (((r)+(l)) >> 1)
long long sum[MAXN];
int used[MAXN * 3];
int n;
long long M;    //
int main()
{
    long long x;
    while( scanf("%d%I64d", &n, &M) != EOF) {
        memset(used, -1, sizeof(used));
        used[100000] = 0;       //TODO
        int ans = 0;
        sum[0] = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%I64d", &x);
            sum[i] = sum[i-1] + x;
//            int tmp = ((sum[i] % M) + M) % M;
            int tmp = (int)((sum[i] % M + M) % M + 100000LL);       //
            if(used[tmp] != -1) ans = max(i - used[tmp], ans);
            else used[tmp] = i;
        }
        printf("%d\n", ans);
    }
    return 0;
}

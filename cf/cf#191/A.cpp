#include <stdio.h>
#define     MAXN    105
int a[MAXN], sum[MAXN];
int n;

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i-1] + (a[i] == 1);
    }
    if(sum[n] == n) {
        printf("%d\n", n-1);
        return 0;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        for(int j = i; j <= n; j++) {
            int s = 0;
            for(int k = i; k <= j; k++) s += (a[k] == 0);
            if(sum[i-1] + sum[n] - sum[j] + s > ans) {
                ans = sum[i-1] + sum[n] - sum[j] + s;
            }
        }
   printf("%d\n", ans);
   return 0;
}

/*
    j - i + 1 -    a[j] - a[i]
*/

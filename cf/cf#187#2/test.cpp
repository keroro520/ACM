#include <stdio.h>
#define     MAXN    200005
long long n, K;
long long d[MAXN];
long long a[MAXN];
int main()
{
    scanf("%I64d%I64d", &n, &K);
    for(int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
    int pre = 1;
    int now = 1;
    d[now] = 0;
    int number = n;

    for(int i = 2; i <= n; i++) {
        now++;
        d[now] = d[now-1] + a[pre]*(now-2);
        //printf("$  %d\n",d[now] - (now-1)*(number-now)*a[i]);
        if(d[now] - (now-1)*(number-now)*a[i] < K) {
            printf("%d\n", i);
            now--;
            number--;
        } else {
            pre = now;
        }
    }
    return 0;
}

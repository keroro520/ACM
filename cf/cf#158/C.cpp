/*
    贪心
*/
#include <algorithm>
#include <stdio.h>
#include <limits.h>
using namespace std;
#define     MAXN    100005
#define     INF     (INT_MAX)
long long  a[MAXN];
long long  n;
int       main()
{
    long long  X, Min = INF;
    scanf("%I64d%I64d", &n, &X);
    X--;
    for(long long  i = 0; i < n; i++) {    
        scanf("%I64d", &a[i]);
        Min = min(Min, a[i]);
    }
    for(long long  i = 0;i < n; i++) a[i] -= Min;
    long long  i = X;
    
    while(true) {
        if(a[i] == 0) break;
        i = (i-1 + n) % n;
    }
    if(i == X) a[i] = Min * n;
    else a[i] = Min * n + (i < X ? X - i : n - (i - X));

    while(true) {
        if(i == X) break;
        i = (i + 1 + n) % n;
        a[i]--;
    }
    for(long long  i = 0; i < n; i++) printf("%I64d ", a[i]);
    printf("\n");
    return 0;
}

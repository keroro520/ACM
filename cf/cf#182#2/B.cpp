#include <stdio.h>
long long song[500001];

int main()
{
    int n, query;
    int x, y;
    scanf("%d%d", &n, &query);
    song[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%I64d%I64d", &x, &y);
        song[i] = song[i-1] + x * y;
    }
    int now = 0, moment;
    while(query--) {
        scanf("%d", &moment);
        for( ; song[now] < moment; now++) ;
        printf("%d\n", now);
    }
    return 0;
}

#include <stdio.h>

int sum[3];
int n, L;
int main()
{
    int t, d;
    scanf("%d%d", &n, &L);
    while(n--) {
        scanf("%d%d", &t, &d);
        if(d == -1) sum[t] += 1;
        else if(d <= L) sum[t] += 2;
        else sum[t] += 3;
    }
    printf("%d:%d\n", sum[1], sum[2]);
}

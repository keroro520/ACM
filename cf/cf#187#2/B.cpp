#include <stdio.h>
#define     MAXN        100005
int a[MAXN], task[MAXN];
int sum[MAXN];
int top, n;
int main()
{
    int m, x,y, op;
    scanf("%d%d", &n, &m);
    for(int i = 1; i<= n; i++) scanf("%d", &a[i]);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &x, &y);
            a[x] = y;
            task[x] = top;
        } else if(op == 3) {
            scanf("%d", &x);
            a[x] += sum[top] - sum[task[x]];
            task[x] = top;
            printf("%d\n", a[x]);
        } else {
            scanf("%d", &y);
            sum[top+1] = sum[top] + y;
            top++;
        }
    }
    return 0;
}

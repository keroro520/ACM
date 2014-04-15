#include <stdio.h>

int f[101];
int n;
int main()
{
    int cases, m, x,y,z;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &f[i]);
        scanf("%d", &m);
        while(m--) {
            scanf("%d%d%d", &x, &y, &z);
            f[y] = f[y] > z ? z : f[y];
        }
        int sum = 0;
        for(int i = 1; i <= n; i++) sum += f[i];
        printf("%d\n", sum);
    }
    return 0;
}

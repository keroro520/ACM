#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = n + m - 1;
    printf("%d\n", ans);
    for(int i = 1; i <= m; i++) printf("%d %d\n", 1, i);
    for(int i = 2; i <= n; i++) printf("%d %d\n", i, 1);
    return 0;
}

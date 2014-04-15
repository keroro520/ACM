#include <stdio.h>
#include <string.h>

int f[100][1001];
int value[100], weight[100];

int max(int x, int y) { if (x > y) return x ; else return y; }

int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    for(int i = 0; i < n; i++)
            scanf("%d%d", weight+i, value+i);
    
    memset(f, 0, sizeof(f));
    f[0][weight[0]] = value[0];
    for(int i = 1; i < n; i++) 
        for(int w = m; w >= 0; w--) {
            f[i][w] = f[i-1][w];
            if(w >= weight[i]) 
                f[i][w] = max(f[i][w], f[i-1][w-weight[i]] + value[i]);
            }

    int ans = 0;
    for(int w = 0; w <= m; w++)
        if(ans < f[n-1][w]) ans = f[n-1][w];
    printf("%d\n", ans);
    return 0;
}

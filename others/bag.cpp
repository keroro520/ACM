#include <string.h>
#include <stdio.h>
int f[12881];
int weight[3403], value[3403];

int max(int x, int y)
{
    if (x > y) return x ; else return y;
}
int main()
{
    //freopen("in", "r", stdin);
    //freopen("out", "w", stdout);
    int W, n;
    scanf("%d%d", &n, &W);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &weight[i], value+i);

    memset(f, 0, sizeof(f));
    for(int i = 0; i < n; i++)
        //for(int w = 0; w <= W; w++) {
        for(int w = W; w >= 0; w--) {
            if (w >= weight[i]) 
                f[w] = max(f[w], f[w-weight[i]] + value[i]);
        }

    int ans = 0;
    for(int w = W; w >= 0; w--)
        if(ans < f[w]) ans = f[w];
    printf("%d\n" , ans);
    return 0;
}

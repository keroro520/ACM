/*
    简单状压DP

    wa了几次都是白痴错误。
*/
#include <stdio.h>
#include <string.h>
#define     N       20
#define     INF     99999999

int n, m, f[(1<<N)+10], s[205], p[205], ori[25];
inline void Add(int bit, int price)
{
    p[m] = price, s[m++] = (1 << bit);
}
int main()
{
    int tmp, k, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &ori[i]);
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &p[i], &k);
        tmp = 0;
        while(k--) {
            scanf("%d", &x);
            tmp |= (1 << (x-1));
        }
        s[i] = tmp;
    }
    scanf("%d", &k);
    tmp = 0;
    while(k--) {
        scanf("%d", &x);
        tmp |= (1 << (x-1));
        Add(x-1, ori[x-1]);
    }
    for(int top = (1<<n), i = 0; i < top; i++) f[i] = INF;
    f[tmp] = 0;
    for(int i = 0; i < m; i++) s[i] &= tmp;
    for(int i = 0; i < m; i++)
        for(int top = (1 << n), j = 0; j < top; j++) if(f[j] != INF) {
            tmp = (s[i] ^ j) & j;
            if(tmp == j || f[tmp] <= f[j] + p[i]) continue;
            f[tmp] = f[j] + p[i];
        }
    printf("%d\n", f[0]);
    return 0;
}

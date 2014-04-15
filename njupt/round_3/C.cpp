#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    4000
#define     MAXM    13000
int n, M;
int w[MAXN], v[MAXN];
int f[MAXM];

int main()
{
    scanf("%d%d", &n, &M);
    for(int i = 0; i < n; i++) scanf("%d%d", &w[i], &v[i]);
    for(int i = 0; i < n; i++)
        for(int j = M; j >= w[i]; j--)
            f[j] = max(f[j], f[j-w[i]]+v[i]);
    int ans = 0;
    for(int i = 0; i <= M; i++) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}

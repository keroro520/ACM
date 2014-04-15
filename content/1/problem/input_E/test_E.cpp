#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    100005
int n, m;
long long a[MAXN], b[MAXN];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
    for(int i = 0; i < m; i++) scanf("%lld", &b[i]);
    long long ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) ans = max(ans, a[i] ^ b[j]);
    printf("%lld\n", ans);
    return 0;
}

#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    100005
long long v[MAXN], color[MAXN], f[MAXN][3], same[MAXN], diff[MAXN], pos[MAXN];
int n;
void init()
{
    for(int i = 1 ; i <= n; i++) {
        same[i] = pos[color[i]];
        pos[color[i]] = i;
    }
    color[0] = -99999999;
    for(int i = 1; i <= n; i++) 
        if(color[i] != color[i-1]) diff[i] = i-1;
        else diff[i] = diff[i-1];
}
long long  work3(long long a, long long b)
{
    long long ans = 0;
    f[0][0] = f[0][1] = f[0][2] = -999999999999;
    for(int i = 1; i <= n; i++) {
        int j = same[i], k = diff[i];
        f[i][0] = max(max(f[j][0], f[j][1]), f[j][2]);
        f[i][0] = max(f[i][0], max(max(f[k][0], f[k][1]), f[k][2]));
        f[i][1] = max(v[i]*b, max(f[j][1], f[j][2]) + v[i] * a);
        f[i][2] = max(v[i]*b, max(f[k][1], f[k][2]) + v[i] * b);
        //printf("%d  %d  %d\n", f[i][0], f[i][1], f[i][2]);
        ans = max(ans, max(f[i][0], max(f[i][1], f[i][2])));
    }
    return ans;
}

int main()
{
    long long  a, b;
    int q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%lld", &v[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &color[i]);
    init();
    while(q--) {
        scanf("%lld%lld", &a, &b);
        printf("%lld\n", work3(a, b));
    }
    return 0;
}

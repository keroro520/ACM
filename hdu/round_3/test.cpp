#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    50005

int a[MAXN], g[MAXN], f[MAXN];
int tmp[MAXN];
int n;
void init()
{
    //memset(f, 0, sizeof(f));
    //memset(g, 0, sizeof(g));
    for(int i = 1; i <= n; i++) {
        //memcpy(tmp, g, sizeof(g));
//        for(int j = i; j <= n; j++) {
//            f[i][j] = max(g[a[i]], f[i][j-1]);
//            int x = a[j];
//            while(x <= n) {
//                g[x] = max(g[x], a[j]);
//                x += a[j];
//            }
//        }
//        for(int j = 1; j <= n; j++) if(g[j] == a[i]) g[j] = tmp[j];
    }
}
int main()
{
    int cases, query, l, r;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        init();
        scanf("%d", &query) ;
        while(query--) {
            scanf("%d%d", &l, &r);
            printf("%d\n", f[l][r]);
        }
    }
    return 0;
}

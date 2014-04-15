#include <stdio.h>
#include <string.h>
#define     MAXN        105
int a[MAXN][MAXN];
bool boo[MAXN][MAXN];

void init()
{
    memset(boo, false, sizeof(boo));
}
void build(int n, int m)
{
    for(int i = 1; i <= m; i++)
        for(int j = 3; j <= n; j++)
           for(int k = 1; k <= n; k++) if(!boo[i][k]) {
                boo[i][k] = true;
                a[i][j] = k;
                break;
           }
}
int main()
{
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        if(n > m) {
            for(int i = 1; i <= m; i++) a[i][1] = i, a[i][2] = n, boo[i][i] = boo[i][n] = true;
            build(n, m);
        } else {
            int p = 1; 
            for(int i = 1; i <= m; i++) {
                a[i][1] = p++;
                if(p == n+1) p = 1;
                boo[i][a[i][1]] = true;
            }
            p = n;
            for(int i = 1; i <= m; i++) {
                if(a[i][1] != p) a[i][2] = p;
                else {
                    p--;
                    if(p == 0) p = n;
                    a[i][2] = p;
                }
                boo[i][a[i][2]] = true;
            }
            build(n, m);
        }
        for(int i = 1; i <= m; i++) 
            for(int j = 1; j <= n; j++) printf("%d%c", a[i][j], j == n ? '\n' : ' ');
    }
    return 0;
}

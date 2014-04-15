#include <stdio.h>
#define     MAXN    105
int b[MAXN], d[MAXN];
bool path[MAXN][MAXN];
int n;
int main()
{
    int x;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);//scanf("%d", &x), b[x] = i;
    for(int i = 1; i <= n; i++) path[i][i] = true;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
        if(i - d[i] > 0) {
            path[i][i-d[i]] = path[i-d[i]][i] = true;
        }
        if(i + d[i] <= n) {
            path[i][i+d[i]] = path[i+d[i]][i] = true;
        }
    }
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++) if(i != k)
            for(int j = 1; j <= n; j++) if(i != j && j != k) 
                path[i][j] = path[i][j] || (path[i][k]&&path[k][j]);
    bool flag = true;
    for(int i = 1; i <= n && flag; i++) 
        if(path[i][b[i]] == false) flag = false;
    printf(flag ? "YES\n" : "NO\n");
    return 0;
}

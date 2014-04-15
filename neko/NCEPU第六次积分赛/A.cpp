#include <stdio.h>
#include <string.h>
#define     MAXN    10
const int dx[4] = {0, 1, 0, -1} ;
const int dy[4] = {1, 0, -1, 0} ;
int f[MAXN][MAXN], a[MAXN][MAXN], pre[MAXN][MAXN][2];
int n = 5, m = 5;
void dfs(int x, int y)
{
    int step = f[x][y];
    for(int i = 0; i < 4; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if(tx < 0 || n <= tx || ty < 0 || m <= ty || a[tx][ty] == 1) continue;
        if(f[tx][ty] > step+1) {
            f[tx][ty] = step+1;        
            pre[tx][ty][0] = x;
            pre[tx][ty][1] = y;
            dfs(tx, ty);
        }
    }
}
void output(int x, int y)
{
    if(x == 0 && y == 0) {
        printf("(%d, %d)\n", x, y);
        return ;
    }
    output(pre[x][y][0], pre[x][y][1]);
    printf("(%d, %d)\n", x, y);
}
int main()
{
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &a[i][j]);
    memset(f, 127, sizeof(f));
    f[0][0] = 0;
    dfs(0, 0);
    output(n-1, m-1);
    return 0;
}


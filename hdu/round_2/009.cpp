#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXX    105
#define     debug   printf("!\n")
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1 ,0, 1};
bool boo[MAXX][MAXX], used[MAXX][MAXX];
int path[MAXX][MAXX];

int dfs(int x, int y)
{
    used[x][y] = true;
    int sum = 0;
    for(int d = 0; d < 4; d++) {
        int tx = x + dx[d], ty = y + dy[d];
        if(tx < 0 || ty < 0 || tx > 100  || ty > 100 ) continue;
        if(d == 0 && (path[x][y] != 1 && path[x][y] != 3)) continue;
        if(d == 2 && (path[x-1][y] != 1 && path[x-1][y] != 3)) continue;

        if(d == 3 && (path[x][y] != 2 && path[x][y] != 3)) continue;
        if(d == 1 && (path[x][y-1] != 2 && path[x][y-1] != 3)) continue;
        if(!used[tx][ty]) sum += dfs(tx, ty) + 1;
    }
    return sum;
}
void init()
{
    memset(used, false, sizeof(used));
    memset(boo,  false, sizeof(boo));
    memset(path, 0, sizeof(path));
}
int main()
{
    int n, m, x, y;
    while(scanf("%d%d", &n, &m) , n + m) {
        init();
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            boo[x][y] = boo[x+1][y] = true;
            path[x][y] = 1;
        }
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            boo[x][y] = boo[x][y-1] = true;
            path[x][y] += 2;
        }
        int ans = 0;
        for(int x = 0; x <= 100 ; x++)
            for(int y = 0; y <= 100 ; y++) if(boo[x][y] && !used[x][y]) {
                int result = dfs(x, y);
                if(result >= 2) ans += (1+result)/2;
                else ans += result;
            }
        printf("%d\n", ans);
    }
}

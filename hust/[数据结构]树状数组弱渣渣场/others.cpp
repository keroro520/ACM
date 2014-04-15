// 如果忘记了这道题是什么。。直接删掉吧 
#include <stdio.h>
#include <string.h>
#include <deque>
#include <vector>
#include <math.h>
using namespace std;
#define     debug       printf("!\n")
#define     ZERO        0.001
#define     INF         9999999.999
#define     MAXN        2005
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
bool a[MAXN][MAXN];
int vis[MAXN][MAXN];
float dis[MAXN][MAXN];
int n, when = 1;

typedef  pair<int,int> Pair ;
deque< Pair > Q;

float Dis(int x1, int y1, int x2, int y2)
{
    return sqrt(1.0 * ((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}
bool check(int x, int y)
{
    return !(x <= 0 || y <= 0 || x > n || y > n || a[x][y]);
}
void calc_dis()
{
    while(!Q.empty()) {
        int x = Q.front().first, y = Q.front().second;
        Q.pop_front();
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++) {
                float tmp = Dis(i, j, x, y);
                if(dis[i][j] > tmp) dis[i][j] = tmp;
            }
    }
}
void init()
{
    Q.clear();
    memset(a, false, sizeof(a));
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++) dis[x][y] = INF;
}
bool dfs(int x, int y, float limit)
{
    vis[x][y] = when;
    if(x == n && y == n) return true;
    for(int d = 0; d < 4; d++) {
        int tx = x + dx[d], ty = y + dy[d];
        if(check(tx, ty) && vis[tx][ty] != when && dis[tx][ty] >= limit) {
            if(dfs(tx, ty, limit)) return true;
        }
    }
    return false;
}
int main()
{
    int cases, M, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &M);
        init();
        while(M--) {
            scanf("%d%d", &x, &y);
            a[x][y] = true;
            Q.push_back(Pair(x, y));
            //vis[x][y] = true;
            dis[x][y] = 0;
        }
        calc_dis();
        float r = sqrt(n*n*2.0), l = 0, mid, ans;
        while(r - l > ZERO) {
            mid = (l + r) / 2;
            when++;
            if(dfs(1, 1, mid)) ans = mid, l = mid;
            else r = mid;
        }
        printf("%.2f\n", ans);
    }
    return 0;
}

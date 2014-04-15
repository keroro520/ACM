/*
    简单状压DP

    题意：在n*m格子里挖矿，问从初始点遍历完标记为‘g’的点再走回到初始点最少需要的步数。一步能走周围8个格子。

    思路：f[x][i] 表搞完状态x后，在i点结束的最少步数。
          特判没有'g'格的情况.
*/
//lightoj 1057
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     N       17
inline char rdc() { scanf(" "); return getchar(); }
int f[1<<N][N], dis[N][N], gold[N][2];
int num, sx, sy;
int Dis(int i, int j)
{
    return max(abs(gold[i][0]-gold[j][0]), abs(gold[i][1]-gold[j][1]));
}
void init()
{
    memset(f, 127, sizeof(f));
    num = 0;
}
int main()
{
    int n, m, cases , Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < n; i++) 
            for(int j = 0; j < m; j++) {
                char ch = rdc();
                if(ch == 'x') sx = i, sy = j;
                else if(ch == 'g') gold[num][0] = i, gold[num++][1] = j;
            }
        for(int i = 0; i < num; i++)
            for(int j = 0; j < num; j++) dis[i][j] = Dis(i,j) ;
        for(int i = 0; i < num; i++) f[1<<i][i] = max(abs(gold[i][0]-sx), abs(gold[i][1]-sy));
        for(int top = (1<<num), i = 1; i < top; i++)
            for(int k = 0; k < num; k++) if(!((1<<k) & i))
                for(int j = 0; j < num; j++) if((1<<j) & i) {
                    int y = i | (1<<k);
                    f[y][k] = min(f[y][k], f[i][j] + dis[j][k]);
            }
        int ans = 9999999;
        for(int i = 0; i < num; i++) ans = min(ans, f[(1<<num)-1][i] + max(abs(gold[i][0]-sx), abs(gold[i][1]-sy)));
        if(num == 0) { ans = 0; }
        printf("Case %d: %d\n", ++Cas, ans);
    }
    return 0;
}

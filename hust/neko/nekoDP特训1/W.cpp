/*
    KM  二分图匹配    MCMF   DP  搜索   好题
    题意：在8*8棋盘上，给出8个皇后的初始位置，要求移动这8个皇后使得皇后之间互不攻击。皇后移动一步可以沿直线或对角线移动任意个格子，但不能跨过一个原本有皇后的格，即会被有皇后的格挡住。皇后的攻击方式跟移动方式一样的。    问最小移动总步数。


    思路：neko最初给我看的时候我第一反应是状压DP，但感觉很复杂，搞不动。
          他说只要能证明一个结论，这道题就很简单了。要证：存在一种最终布局，使得最优移动过程中任何有皇后不互挡，也就是说我们可以不用考虑“不能跨皇后”这个限制，直接“穿越”做。
          我画了个4*4的图，然后幸运地得出了证明：假设现在在i点的皇后要到k点去（那k点当然是最终布局的皇后点啦，不然到那里去干嘛），中间有个j（j点有个皇后）隔住了。 那么k与j就在一条直线上，也就是说 j 不是最终皇后点，那么 j 就应该要挪到她相应的点去，等她挪完后就不挡住i 到达 k 点了。

          证了上述结论就好办了，用二分图带权匹配KM算法或者最大流最小费用流MCMF都可以做，费用为移动步数。
          我是用KM 做的。先预处理出8*8上所有合理布局，一共92种。然后对于每种合理布局，拿来跟初始布局搞二分图带权匹配。易知这个二分图是完全二分图（表述不太准确，就是X部Y部两两有边）。

          这道题是归类在DP上的 orz... 在vj上有人用搜索+dp做... 
*/
//lightoj 1061
#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     N       8
#define     ABS(x)      ((x) > 0 ? (x) : (-(x)))
int l[3][N*2], X[N], map[100][N], a[N][2];              //map[i][x] 存第i种合理布局的x行皇后应该放的列数
int edge[N][N], LX[N], LY[N], link[N], slack[N];
bool visx[N], visy[N];
int Top = 0;
void label(int row, int col)
{
    l[0][col] ^= 1;
    l[1][row+col] ^= 1;
    l[2][row-col+N] ^= 1;
}
bool check(int row, int col)
{
    return l[0][col] && l[1][row+col] && l[2][row-col+N];
}
void init(int row)
{
    if(row == N) {
        for(int i = 0; i < N; i++) map[Top][i] = X[i];
        Top++;
        return ;
    }
    for(int i = 0; i < N; i++) {
        if(check(row, i)) {
            X[row] = i;
            label(row, i);
            init(row+1);
            label(row, i);
        }
    }
}
inline char rdc() { scanf(" "); return getchar(); }
void read_board()
{
    int k = 0;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(rdc() == 'q') a[k][0] = i, a[k][1] = j, k++;
}
int dis(int x1, int y1, int x2, int y2)
{
    if(x1 == x2 && y1 == y2) return 0;
    if(x1 == x2 || y1 == y2) return 1;
    if(x1 + y1 == x2 + y2 || (x1 - y1) == (x2 - y2)) return 1;
    return 2;
}
void build(int * map) 
{
    for(int i = 0; i < N; i++) {
        int x = a[i][0], y = a[i][1];
        for(int j = 0; j < N; j++) {
            edge[i][j] = -dis(x, y, j, map[j]);
        }
    }
}
bool find(int u)
{
    visx[u] = true;
    for(int v = 0; v < N; v++) if(!visy[v]) {
        int rest = LX[u] + LY[v] - edge[u][v];
        if(rest == 0) {
            visy[v] = true;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;
                return true;
            }
        } else slack[v] = min(slack[v], rest);
    }
    return false;
}
int KM()
{
    memset(LX, 128, sizeof(LX));
    memset(LY,   0, sizeof(LY));
    memset(link,-1, sizeof(link));
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) LX[i] = max(LX[i], edge[i][j]);
    for(int start = 0; start < N; start ++) {
        for(int i = 0; i < N; i++) slack[i] = (INT_MAX);
        while(true) {
            memset(visx, false, sizeof(visx));
            memset(visy, false, sizeof(visy));
            if(find(start)) break;
            else {
                int d = (INT_MAX);
                for(int i = 0; i < N; i++) if(!visy[i]) d = min(d, slack[i]);
                //if(d == (INT_MAX)) return -1;
                for(int i = 0; i < N; i++) if(visx[i]) LX[i] -= d;
                for(int i = 0; i < N; i++)
                    if(visy[i]) LY[i] += d;
                    else slack[i] -= d;
            }
        }
    }
    int sum = 0;
    for(int i = 0; i < N; i++) sum += edge[link[i]][i];
    return -sum;
}
int main()
{
    int cases, Cas = 0;
    for(int i = 0; i < 3; i++) for(int j = 0; j < 2*N; j++) l[i][j] = 1;
    init(0);
    scanf("%d", &cases);
    while(cases--) {
        read_board();
        int ans = 17;
        for(int i = 0; i < Top; i++) {                  //枚举每一种最终布局
            build(map[i]);
            ans = min(ans, KM());
        }
        printf("Case %d: %d\n", ++Cas, ans);
    }
    return 0;
}

/*
    二分图最大匹配  经典题

    题意：一张nxn的图，图上有的格子有东西挡着，问一个在图上最多放几个炮台能覆盖整张图，且不会火力部重叠。若两个格子同行或同列且中间没有东西挡住的话就会重叠。

    思路：经典二分图最大匹配，让我对格子二分图匹配有了更好的理解。
          建图：依然还是行元素在二分图的X部，列元素在Y部。不同的是，因为有'#'阻断元素的存在，若某一行被'#'分成两部分，则要把该行分成两部分，对应于二分图的话就是拆成两个点，当然都属于X部。分成几部分就是几个点。
          列元素同理。
          代码里面用count-row和count_col统计行/列元素个数。其实就是把n*n分成多少个区间。

          接着是连边：若行区间i 和 列区间j有交集的话则连边<i,j>     代码里面用path[i][j]表示，比较低效，随便了。


*/
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define debug   printf("!\n")
#define     MAXN    50
int n, count_row, count_col;
int path[MAXN][MAXN], link[MAXN];
int R[MAXN][MAXN], C[MAXN][MAXN];
bool visit[MAXN];
string map[MAXN];
void init()
{
    count_row = count_col = 0;
    memset(link, -1, sizeof(link));
    memset(path, false, sizeof(path));
}
bool find(int u)
{
    for(int v = 0; v < count_col; v++) if(path[u][v] && visit[v] == false) {
        visit[v] = true;
        if(link[v] == -1 || find(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;   
}
int hungary()
{
    int ans = 0;
    for(int i = 0; i < count_row; i++) {
        memset(visit, false, sizeof(visit));
        ans += find(i);
    }
    return ans;
}
int main()
{
    while(scanf("%d", &n) != EOF) {
        init();
        for(int row = 0; row < n; row++) cin >> map[row];

        for(int row = 0; row < n; row++) {          //拆分行区间
            int p = 0;
            while(p < n) {
                if(map[row][p] == 'X') count_row++;
                else R[row][p] = count_row;
                p++;
            }
            count_row++;
        }
        for(int col = 0; col < n; col++) {          //拆分列区间
            int p = 0;
            while(p < n) {
                if(map[p][col] == 'X') count_col++;
                else C[p][col] = count_col;
                p++;
            }
            count_col++;
        }
        for(int row = 0; row < n; row++)
            for(int col = 0; col < n; col++) if(map[row][col] == '.')
                path[R[row][col]][C[row][col]] = true;

        printf("%d\n", hungary());
    }
    return 0;
}

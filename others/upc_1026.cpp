/*
    Weird Coloring : 给一个无向图的边涂色(0,1,2), 使得颜色总和最小, 满足条件 : 若给某边涂上颜色0, 则要求它的相邻边至少有一条是涂上2的边. 所谓的"相邻边"即有公共点的边


    贪心失败了 : 每次找一条相邻边最多的边e, 把它涂上2, 则其相邻边涂上0, 相当于把e与e的相邻边从图中删掉. 更新图的数据(相邻边数), 再重复该步骤直至没有相邻边. 最后处理一下孤立边.

    失败原因还不知道.
*/
#include <string.h>
#include <stdio.h>
#define     M   31
struct Edge {int x, y; } e[M];
int n, m, ans;
int num[M];
bool connect[M][M];

bool check_connect(int i, int j) {
    return  e[i].x == e[j].x || e[i].x == e[j].y ||
            e[i].y == e[j].x || e[i].y == e[j].y ;
}
void init()
{
    bool boo[M][M];
    memset(boo, false, sizeof(boo));
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &e[i].x, &e[i].y);
        if(boo[e[i].x][e[i].y]) m--, i--;
        else boo[e[i].x][e[i].y] = boo[e[i].y][e[i].x] = true;
    }
    for(int i = 0; i < m-1; i++)
        for(int j = i+1; j < m; j++) 
            connect[i][j] = connect[j][i] = check_connect(i, j);
}
bool solve()
{
    //构图
    memset(num, 0, sizeof(int)*(m+1));
    for(int i = 0; i < m-1; i++) if(e[i].x != -1)
        for(int j = i+1; j < m; j++) 
            if(e[j].x != -1 && connect[i][j]) {
                num[i]++;
                num[j]++;
            }
    //找cons最多的边
    int tmps = 0, tmpi = 0;
    for(int i = 0; i < m; i++) if(e[i].x != -1)
        if(tmps < num[i]) {
            tmps = num[i];
            tmpi = i;
        }

    if(tmps == 0) return true;

    ans += 2;
    //删边
    printf("$ %d    %d %d\t\t%d\n", tmpi+1, e[tmpi].x, e[tmpi].y, num[tmpi]);
    e[tmpi].x = -1;
    for(int i = 0; i < m; i++) 
        if(connect[i][tmpi]) e[i].x = -1;
    
    return false;
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        init();
        ans = 0;
        while(!solve());
        for(int i = 0; i < m; i++) 
            if(e[i].x != -1) ans++, printf("rest : %d %d\n", e[i].x, e[i].y);
        printf("%d\n", ans);
    }
    return 0;
}
/*
http://acm.upc.edu.cn/problem.php?cid=1026&pid=5
*/

/*
    二分图多重匹配  启发题

    题意：题意：末日逃亡，n个人逃往m个星球，一个人只能在某些星球上生存。一个星球最多居住人口有上限。求最后是否可以让所有人都逃离地球

    思路：一般的二分图匹配是一对一的，link[]贮存Y部的匹配点。
          这道题是多对一的，也就是星球能与多个人同时匹配，方法就是扩展link的含义，给它加一维，贮存与星球匹配的所有人。
          link[]含义扩展了，接下来就扩展匈牙利算法，原始的二分图最大匹配匈牙利算法在找未盖点i的增广路时，对于其邻接点j，若j也是未盖点，则i,j匹配，否则尝试删除<link[j], j> 边，向上找增广路，如果找到了，则i,j匹配，link[j] = i.  
          现在扩展成若星球j已匹配的人数 < capacity[j]，则人类i加到其匹配列表里，即link[j].push_back(i)，否则尝试删除星球j的已匹配边<j, k>，从k向上寻找增广路，若找到，则用i代替k的位置link[j][k] = i;
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    100005
#define     MAXM    11
bool path[MAXN][MAXM];
int  cap[MAXM];
int link[MAXM][MAXN];
bool visit[MAXM];
int n, m;

void init()
{
    for(int i = 0; i < m; i++) link[i][0] = 0;
}
bool find(int u)
{
    for(int v = 0; v < m; v++) if(path[u][v] && visit[v] == false){
        visit[v] = true;
        if(link[v][0] < cap[v]) {
            link[v][++link[v][0]] = v;
            return true;
        }
        for(int i = 1; i <= link[v][0]; i++)
            if(find(link[v][i])) {
                link[v][i] = u;
                return true;
            }
   }
   return false;
}
bool hungary()
{
    for(int i = 0; i < n; i++) {
        memset(visit, false, sizeof(visit));
        if(!find(i)) return false;
    }
    return true;
}
int main()
{
    int x;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < n; i++) 
            for(int j = 0; j < m; j++) {
                scanf("%d", &x);
                path[i][j] = x;
            }
        for(int i = 0; i < m; i++) scanf("%d", &cap[i]);

        printf(hungary() ? "YES\n" : "NO\n");
    }
    return 0;
}

/*
    双连通

    求割点以及去掉割点后会把原图分成几部分.

    割点u的充要条件：u是生成树的根节点，则root至少有两个子树
                    u不是根节点，则至少有一个子树w，使得low[v] >= dfn[u]
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     MAXN    1005

int root , son_of_root , edge_num, Index;
int low[MAXN], dfn[MAXN], head[MAXN], subnet[MAXN];
bool visit[MAXN*MAXN*2], path[MAXN][MAXN];
struct Edge { int v, next ; } edge[MAXN*MAXN*2] ;
void Tarjan(int u)
{
    dfn[u] = low[u] = ++Index;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        if(visit[k]) continue;
        visit[k] = visit[k^1] = true;
        int v = edge[k].v;
        if(dfn[v] == -1) {
            Tarjan(v);
            if(dfn[u] <= low[v]) subnet[u]++;       //子树个数++
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], dfn[v]);        //换成low怎么样？
    }
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
    edge[edge_num].v = u;
    edge[edge_num].next = head[v];
    head[v] = edge_num++;
}
void init()
{
    edge_num = 0;
    Index = 0;
    memset(head, -1, sizeof(head));
    memset(dfn,  -1, sizeof(dfn));
    memset(low,  -1, sizeof(low));
    memset(subnet, 0, sizeof(subnet));
    memset(path, false, sizeof(path));
    memset(visit, false, sizeof(visit));
}
int main()
{
    int cases = 0, x, y;
    while(scanf("%d", &x) , x) {
        scanf("%d", &y);
        init();
        while(true) {
            if(path[x][y]) continue;
            path[x][y] = path[y][x] = true;
            add_edge(x, y);
            //printf("%d  %d\n", x, y);
            scanf("%d", &x);
            if(x == 0) break;
            scanf("%d", &y);
        }
        root = 1;
        Tarjan(1);
        subnet[root] = (subnet[1] <= 1 ?  0 : subnet[1] - 1);       //这里WA了一次
        bool flag = false;
        printf("Network #%d\n", ++cases);
        for(int i = 1; i <= 1000; i++) if(subnet[i]) {
            flag = true;
            printf("  SPF node %d leaves %d subnets\n", i, subnet[i]+1);    //加1是向上子树
        }
        puts(flag ? "" : "  No SPF nodes\n");
    }
    return 0;
}

/*
    树   路径   树的直径
    题意：给一棵树，Q个询问，问要遍历k个节点最短要走多少距离。边权都为1，起点从哪儿开始都可以。

    思路：  当k <= dia的时候，ans = k - 1
            当k >  dia的时候，ans = dia - 1 + (k - dia) * 2



    比赛的时候没想出来。。太弱了。。。
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    100005
int head[MAXN];
struct Edge { int v, next; } edge[MAXN * 2];
int dia, node, n, edge_num;
void init()
{
    dia = 0;
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void dfs(int u, int f, int len)
{
    if(len > dia) {
        dia = len;
        node = u;
    }
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(v == f) continue;
        dfs(v, u, len+1);
    }
}

int main()
{
    int cases, query, x, y, k;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        dfs(1, -1, 1);
        dfs(node, -1, 1);
        while(query--) {
            scanf("%d", &k);
            if(k <= dia) printf("%d\n", k - 1);
            else printf("%d\n", dia - 1 + (k - dia) * 2);
        }
    }
    return 0;
}

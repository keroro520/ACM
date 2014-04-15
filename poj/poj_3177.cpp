/*
    双连通  [构造双连通]
    题目大意 : 给了一个有 n(1<=n<=5000) 个点 m(n-1<=m<=10000) 个边的连通的无向图，现在问最少需要添加多少条边才能使得整个图中所有的点对之间至少存在两条没有交集的路径？

    思路：缩点，对缩之后的点建图，统计其叶子节点的个数leave，答案为(leave+1)/2
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
using namespace std;
#define     MAXN    1005
struct Edge { int v, next; } edge[MAXN* 2];
int head[MAXN], low[MAXN], dfn[MAXN], belong[MAXN], deg[MAXN];
bool in_stack[MAXN], visit[MAXN*2], path[MAXN][MAXN];
int Order, Index, edge_num, n;
stack<int> S;

void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void init()
{
    Index = Order = 1;
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
    S.push(u);
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) if(!visit[k]){
        visit[k] = visit[k^1] = true;
        int v = edge[k].v;
        if(dfn[v] == 0) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        int x;
        do {
            x = S.top();
            S.pop();
            in_stack[x] = false;
            belong[x] = Order;
        } while(x != u);
        Order++;
    }
}
int main()
{
    int r, x, y;
    scanf("%d%d", &n, &r);
    init();
    while(r--) {
        scanf("%d%d", &x, &y);
        if(path[x][y]) continue;
        path[x][y] = path[y][x] = true;
        add_edge(x, y);
        add_edge(y, x);
    }
    Tarjan(1);
    int leave = 0;
    for(int i = 1; i <= n; i++) 
        for(int j = i+1; j <= n; j++) if(path[i][j] && belong[i] != belong[j])
            deg[belong[i]]++, deg[belong[j]]++;
    for(int i = 1; i < Order; i++) leave += (deg[i] == 1);
    printf("%d\n", (leave+1)/2);
    return 0;
}

/*
    求树的重心
    树的重心定义：删掉重心g后，原来的树分成了若干棵子树，要使得这些子树的节点数最大的最小，即Min( Max{ sum_of_nodes(subtree) }

    思路：树形DP
          对于点g，删除g后，剩余有son[k]可子树和一棵向上子树，节点数分别为nodes_of_son[i] 和 n - sum{nodes_of_son}，取最大值
*/
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    20005

struct Node {int v, next;} edge[MAXN*2];
int n, edge_num;
int head[MAXN], son[MAXN], Max[MAXN];
bool visit[MAXN];

void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(visit, false, sizeof(visit));
}
void add_edge(int u, int v)
{
    Node tmp = {v, head[u]};
    edge[edge_num] = tmp;
    head[u] = edge_num;
    edge_num++;
}
void dfs(int u)
{
    visit[u] = true;
    son[u]   = 1;
    Max[u]   = 0;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visit[v]) continue;
        dfs(v);
        son[u] += son[v];
        Max[u] = max(Max[u], son[v]);
    }
    Max[u] = max(Max[u], n - son[u]);
}
int main()
{
    int cases, u, v;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &u, &v);
            add_edge(u, v);
            add_edge(v, u);
        }
        dfs(1);
        int ans = n, ansi = 0;
        for(int i = 1; i <= n; i++) if(ans > Max[i]) {
            ans  = Max[i];
            ansi = i;
        }
        printf("%d %d\n", ansi, ans);
    }
    return 0;
}

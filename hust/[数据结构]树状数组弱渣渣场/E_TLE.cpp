/*
    单纯是树做，TLE
*/
// poj 3321
#include <stdio.h>
#include <string.h>
#define         MAXN        100005
int n, edge_num = 0, head[MAXN], label[MAXN], f[MAXN], father[MAXN];
struct Edge {
    int v, next;
} edge[MAXN * 2];

void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void Update(int u, int add)
{
    label[u] ^= 1;
    do {
        f[u] += add;
        u = father[u];
    } while(u != 0);
}
void build_tree(int root, int prev)
{
    for(int k = head[root]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(prev == v) continue;
        father[v] = root;
        build_tree(v, root);
        f[root] += f[v];
    }
}
int main()
{
    int x, y, query;
    char op[2];
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    for(int i = 1; i <= n; i++) f[i] = label[i] = 1;

    father[1] = 0;
    build_tree(1, 0);
    scanf("%d", &query);
    while(query--) {
        scanf("%s%d", op, &x);
        if(op[0] == 'Q') printf("%d\n", f[x]);
        else Update(x, (label[x] == 0) ? 1 : -1);
    }
    return 0;
}

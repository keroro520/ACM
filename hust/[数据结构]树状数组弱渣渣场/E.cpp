/*
    树状数组 线段树
    单纯是树做，TLE
    dfs中序遍历出序号再树状数组/线段树搞就可以了 : 记录每个节点的序号in[x], 记录该节点的最远子孙节点的序号out[x], 然后x分支的苹果数就是树状数组里面Query(in[x], out[x]-1)
    跟zoj 3686很像
*/
// poj 3321
#include <stdio.h>
#include <string.h>
#define         MAXN        100005
#define         low(x)      ((x)&(-(x)))
int n, Index, edge_num = 0, head[MAXN], c[MAXN], in[MAXN], out[MAXN], label[MAXN];
struct Edge {
    int v, next;
} edge[MAXN * 2];

void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void build_tree(int root, int prev)
{
    in[root] = out[root] = Index--;
    for(int k = head[root]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(prev == v) continue;
        build_tree(v, root);
        out[root] = out[v];
    }
}
void init()
{
    edge_num = 0;
    Index = n;
    memset(head, -1, sizeof(head));
}
int _Query(int pos)
{
    int sum = 0;
    while(pos) {
        sum += c[pos];
        pos -= low(pos);
    }
    return sum;
}
int Query(int l, int r)
{
    return _Query(r) - _Query(l-1);
}
void Update(int pos, int add)
{
    while(pos <= n) {
        c[pos] += add;
        pos += low(pos);
    }
}
int main()
{
    int x, y, query;
    char op[2];
    scanf("%d", &n);
    init();
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    build_tree(1, 0);
    for(int i = 1; i <= n; i++) label[i] = 1, Update(in[i], 1);
    scanf("%d", &query);
    while(query--) {
        scanf("%s%d", op, &x);
        if(op[0] == 'Q') printf("%d\n", Query(out[x], in[x]));
        else {
            Update(in[x], (label[x] == 0) ? 1 : -1);
            label[x] ^= 1;
        }
    }
    return 0;
}

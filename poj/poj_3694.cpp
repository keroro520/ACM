/*
    双连通  缩点  桥  LCA  
    
    题意：给一个无向连通图，问每次新加进一条边后，图中桥的数目。  重边算一条。

    思路：求双连通分量，利用并查集缩点，形成一棵树，树边肯定都是桥，然后每对点x,y,找原图中x,y点对应的新图中的点，如果不是一个点，则向上找它们的LCA,因为它们之间连了一条边，所以这些点到它们的LCA之间的边都不是割边了，找LCA时，先将两点上升到同一层次，然后一起再向上找父亲节点，其间遇到桥就把桥的标记删除，并且答案减1



    

    思路还是挺简单的，不过我做了很久，把调试过程记录下来吧。准确来说的对拍调试过程。
    1. ans是当前桥的数目。两种方法，一种是在Tarjan里面if (dfn[u] <= low[v]) ans++；第二种是直接ans = Order - 1; Order表示连通块的个数，因为缩点之后是一棵树，那树的没一条边都是桥，所以桥数 = 点数 - 1.

    2. 题目没有说当有重边的时候要怎么办，实验表明，当有重边的时候只算一条。那Tarjan的时候有两个办法防止无尽循环，一是在读边的时候就注意有没有重边，则在Tarjan里面可以用visit[]来记录某边是否已经用过；而是改边判为点判，即记录点的父节点，然后递归之前判断一下。
       感觉还是第二种比较省事。这里记一下代码:
          for(int k = head[u]; k != -1; k = edge[k].next) {
                int v  = edge[k].v;
                if(fa[u] == v) continue;    //!!
                if(!dfn[v]) {
                    fa[v] = u;...
            ....
    3. 建缩点之后的树还是挺简单的，可以当作模板了。
    4. 朴素lca的各个语句的位置弄混了...
    5. 下面这句调试语句棒=帮了很多忙
        for(int i = 1; i <= n; i++) printf("# %d\t%d\t%d\n", i, belong[i], deep[belong[i]]);      //查了这里才知道
       
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    200005
#define     MAXM    400005

struct Edge { int v, next; } edge[MAXM * 2];
int  head[MAXN], low[MAXN], dfn[MAXN], belong[MAXN], father[MAXN], deep[MAXN];
bool in_stack[MAXN], ok[MAXN], visit[MAXM * 2], used[MAXN];
int edge_num, Index, Order, S_top, ans , n;
int S[MAXN * 2];
int fa[MAXN];
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void init()
{
    edge_num = 0;
    Index = 1;
    Order = 0;
    S_top = 0;
    ans = 0;
    memset(head, -1, sizeof(head));
    memset(dfn,  0 , sizeof(dfn));
    memset(low,  0 , sizeof(low));
    memset(visit, false, sizeof(visit));
    memset(deep, -1, sizeof(deep));
    memset(in_stack, false, sizeof(in_stack));
    memset(used, false, sizeof(used));
    memset(fa, 0, sizeof(fa));      //有用吗？？？？？
}
void Tarjan(int u)
{
    S[S_top++] = u;
    in_stack[u] = true;
    dfn[u] = low[u] = Index++;
    for(int k = head[u]; k != -1; k = edge[k].next) { //if(!visit[k]) {
        //visit[k] = visit[k^1] = true;
        int v = edge[k].v;
        if(fa[u] == v) continue;        //还有这里。。。 
        if(!dfn[v]) {
            fa[v] = u;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            // if(dfn[u] <= low[v]) ans++;  用这个ans的话在只有一个连通块的时候会错？？？
        } else if(in_stack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        int x;
        do {    
            x = S[--S_top];
            belong[x] = Order;
            in_stack[x] = false;
        } while(x != u);
        Order++;
    }
}
void build(int root, int f)
{
    for(int k = head[root]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(v == f || used[v]) continue;
        used[v] = true;
        if(belong[v] == belong[root]) build(v, root);
        else {
            father[belong[v]] = belong[root];
            build(v, root);
        }
    }
}
int get_depth(int node)
{
    if(-1 != deep[node]) return deep[node];
    return deep[node] = 1 + get_depth(father[node]);
}
void Query(int x, int y)
{
    if(deep[x] < deep[y]) swap(x, y);
    while(deep[x] > deep[y]) {
        ans -= (!ok[x]);
        ok[x] = true;
        x = father[x];          //之前把这一句放在while开始，当然错啦！！
    }
    if(x == y) return ;
    while(true) {
        ans -= (!ok[x]) + (!ok[y]);
        ok[x] = ok[y] = true;
        x = father[x], y = father[y];       //位置很重要，不确定的时候模拟一下即可。
        if(x == y) return ;
    }
}
int main()
{
    int Case = 0, query, x, y, m;
    while(scanf("%d%d", &n, &m) != EOF && n) {
        init();
        while(m--) {
            scanf("%d%d", &x, &y);
            add_edge(x, y);     //先默认没有重边了..结果题目是有重边的
            add_edge(y, x);
        }
        Tarjan(1);
        ans = Order - 1;
        build(1, -1);
        deep[belong[1]] = 0;        //belong[1] != 0！！
        for(int i = 0; i < Order; i++) if(-1 == deep[i]) get_depth(i);
        //for(int i = 1; i <= n; i++) printf("# %d\t%d\t%d\n", i, belong[i], deep[belong[i]]);      //查了这里才知道
        for(int i = 0; i < Order; i++) ok[i] = false;
        printf("Case %d:\n", ++Case);
        scanf("%d", &query);
        while(query--) {
            scanf("%d%d", &x, &y);
            Query(belong[x], belong[y]);
            printf("%d\n", ans);
        }
        printf("\n");
    }
    return 0;
}

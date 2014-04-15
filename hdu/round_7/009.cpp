#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define     bug(x)      printf("# %d\n", x)
#define     debug       printF("!\n")
#define     MAXN        100005
#define     MAXM        150005
#define     MAXQ        100005
struct Edge {
    int v, next;
} edge[MAXM * 2];
class  Quetion {
    public :
    int p, v, id;
    Quetion() { }
    Quetion(int v, int p, int id) : v(v), p(p), id(id) { }
} ;
vector<Quetion> Q[MAXN];
vector<int> adj[MAXN];
bool vis[MAXN], yes[MAXN];
int n, m, S_top, edge_num, Index, Order;
int S[MAXN], head[MAXN], dfn[MAXN], low[MAXN], belong[MAXN], Anc[MAXN], depth[MAXN], f[MAXN];
int ans[MAXQ];

void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void Tarjan(int u)
{
    dfn[u] = low[u] = ++Index;
    S[S_top++] = u;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(f[u] == v) continue;
        if(!dfn[v]) {
            f[v] = u;
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        int x;
        do {
            x = S[--S_top];
            belong[x] = Order;
        } while(x != u);
        Order++;
    }
}
void init()
{
    S_top = edge_num = Index = Order = 0;
    memset(head, -1, sizeof(head));
    memset(dfn, 0, sizeof(dfn));
    memset(yes, false, sizeof(yes));
    memset(ans, 0, sizeof(ans));
    memset(vis, false, sizeof(vis));
    memset(f, -1 , sizeof(f));
    for(int i = 0; i <= n; i++) Q[i].clear();
    for(int i = 0; i <= n; i++) adj[i].clear();
    for(int i = 0; i <= n; i++) Anc[i] = i;
}
int find(int x) { return x == Anc[x] ? x : Anc[x] = find(Anc[x]); }
void Union(int x, int y) { Anc[find(y)] = find(x); }
void LCA(int u, int dep)
{
    vis[u] = true;
    depth[u] = dep;
    for(int Size = adj[u].size(), i = 0; i < Size; i++) {
        int v = adj[u][i];
        if(vis[v]) continue;
        LCA(v, dep+1);
        Union(u, v);
    }
    for(int Size = Q[u].size(), i = 0; i < Size; i++) {
        int v = Q[u][i].v;
        if(!vis[v] || ans[Q[u][i].id] != 0) continue;
        if(!vis[Q[u][i].p] || depth[find(v)] > depth[Q[u][i].p]) ans[Q[u][i].id] = -1;
        else ans[Q[u][i].id] = 1;
    }
}

int main()
{
    int u, v, p, query;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            if(u == v) continue;
            add_edge(u, v);
            add_edge(v, u);
        }
        for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(1);
        for(int x = 1; x <= n; x++) 
            for(int k = head[x]; k != -1; k = edge[k].next) {
                int v = edge[k].v;
                if(belong[x] == belong[v]) continue;
                yes[x] = yes[v] = true;
                adj[belong[x]].push_back(belong[v]);
                adj[belong[v]].push_back(belong[x]);
            }
        scanf("%d", &query);
        for(int i = 0; i < query; i++) {
            scanf("%d%d%d", &u, &v, &p);
            if(u == v) {
                if(u == p) ans[i] = 1;
                else ans[i] = -1;
                continue;
            }
            if(u == p || v == p) {
                ans[i] = 1;
                continue;
            }
            if(belong[u] == belong[v]) {
                if(belong[u] == belong[p]) ans[i] = 1; else ans[i] = -1;
                continue;
            }
            if(belong[u] == belong[p]) {
                if(yes[u]) ans[i] = 1; else ans[i] = -1;
                continue;
            }
            if(belong[v] == belong[p]) {
                if(yes[v]) ans[i] = 1; else ans[i] = -1;
                continue;
            }
            if(yes[p] == false) { ans[i] = -1; continue; }
            Q[belong[u]].push_back(Quetion(belong[v], belong[p], i));
            Q[belong[v]].push_back(Quetion(belong[u], belong[p], i));
        }
        LCA(0, 0);
        for(int i = 0; i < query; i++) puts(ans[i] == 1 ? "Yes" : "No");
    }
    return 0;
}

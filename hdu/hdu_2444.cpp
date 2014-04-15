/*
    二分图最大匹配  简单题

    先用染色法判断是否能构成二分图，再求最大匹配

    ***痛苦的教训：用when来代替多次memset(visit)，可是把when设成局部变量就悲剧了。我一开始是在main()里一个when，然后每次hungary(++when)，还有hungary(int when)里面又有一个形参when...然后，然后就悲剧了，我虽然在hungary里面find(++when)，但是并没有影响到main里面的when....所以还是把when放到全局变量里来。
    
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    205
#define     MAXM    205*205*2
bool FLAG = false;
struct Edge { int v, next; } edge[MAXM];
int color[MAXN], head[MAXN], visit[MAXN], link[MAXN], X[MAXN];
int n, count_X, edge_num;
int Q[MAXN+MAXN];
int when = 0;
void init()
{
    edge_num = 0;
    memset(link, -1, sizeof(link));
    memset(head, -1, sizeof(head));
    memset(color, 0, sizeof(color));
}
void add_edge(int u, int v)
{
    Edge tmp = {v, head[u]};
    edge[edge_num] = tmp;
    head[u] = edge_num;
    edge_num++;
}
bool find(int u)
{
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visit[v] != when) {
            visit[v] = when;
            if(link[v] == -1 || find(link[v])) {
                link[v] = u;   
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ans = 0;
    for(int i = 0; i < count_X; i++) 
        when++, ans += find(X[i]);
    return ans;
}
void build()
{
    count_X = 0;
    for(int i = 1; i <= n; i++)
        if(color[i] == 1) X[count_X++] = i;
}
bool dye()
{
    for(int i = 1; i <= n; i++) if(color[i] == 0) {
        int car = 0, cdr = 0;
        Q[++car] = i;
        color[i] = 1;
        while(car != cdr) {
            int u = Q[++cdr];
            for(int k = head[u]; k != -1; k = edge[k].next) {
                int v = edge[k].v;
                if(color[v] != 0) {
                    if(color[v] == color[u]) return false;
                    else continue;
                }
                color[v] = -color[u];
                Q[++car] = v;
            }
        }
    }
    return true;
}
int main()
{
    int m, x, y;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        for(int i = 0; i < m; i++) {    
            scanf("%d%d", &x, &y);
            add_edge(x, y);
            add_edge(y, x);
        }
        if(!dye()) {
            printf("No\n");
            continue;
        }
        
        build();
        when++;
        printf("%d\n", hungary());
    }
    return 0;
}

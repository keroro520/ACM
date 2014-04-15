#include <deque>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     MAXN    1005
int cat_head[MAXN], mouse_head[MAXN];
bool visit[MAXN], cat_arrive[MAXN], mouse_arrive[MAXN], path[MAXN][MAXN];
struct Edge{ int v, next; } edge[MAXN * MAXN];
int Cat, Mouse, n, edge_num;

void init()
{
    edge_num = 0;
    memset(mouse_head, -1, sizeof(mouse_head));
    memset(cat_head,   -1, sizeof(cat_head));
}
bool dfs(int u)
{
//    printf("! %d\n", u);
    //if(u == Mouse && visit[u]) return true;
    visit[u] = true;
    for(int k = mouse_head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(v == Mouse) return true;
        if(visit[v] || cat_arrive[v]) continue;
        if(dfs(v)) return true;
    }
    return false;
}
void add_edge(int * head, int x, int y)
{
    edge[edge_num].v = y;
    edge[edge_num].next = head[x];
    head[x] = edge_num++;
}
void bfs(int s, int * head)
{
    deque<int> Q;
    Q.push_back(s);
    memset(visit, false, sizeof(visit));
    visit[s] = true;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        for(int k = head[u]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(visit[v]) continue;
            visit[v] = true;
            Q.push_back(v);
        }
    }
}
int main()
{
    int cases, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d%d", &n, &Cat, &Mouse);
        init();
        memset(path, false, sizeof(path));
        while(scanf("%d%d", &x, &y), !(x == -1 && y == -1)) {
            if(!path[x][y]) path[x][y] = true;
            else continue;
            add_edge(cat_head, x, y);
        }
        bfs(Cat, cat_head);
        for(int i = 1; i <= n; i++) cat_arrive[i] = visit[i];
        memset(path, false, sizeof(path));
        while(scanf("%d%d", &x, &y), !(x == -1 && y == -1)) {
            if(!path[x][y]) path[x][y] = true;
            else continue;
            add_edge(mouse_head, x, y);
        }
        bfs(Mouse, mouse_head);
        for(int i = 1; i <= n; i++) mouse_arrive[i] = visit[i];
        bool flag = false;
        for(int i = 1; i <= n; i++) if(mouse_arrive[i] && cat_arrive[i]) { flag = true; break; }
        printf(flag ? "Y " : "N ");
        memset(visit, false, sizeof(visit));
        printf(cat_arrive[Mouse] || !dfs(Mouse)? "N\n" : "Y\n");
    }
    return 0;
}

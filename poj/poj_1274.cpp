/*
    二分图最大匹配   模板题
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    205
#define     MAXM    205*205
struct Edge { int v, next; } edge[MAXM];
int n, m, edge_num;
int head[MAXN], link[MAXN], visit[MAXN];

void add_edge(int u, int v)
{
    Edge tmp = {v, head[u]};
    edge[edge_num] = tmp;
    head[u] = edge_num;
    edge_num++;
}
bool find(int u, int when) 
{
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(visit[v] != when) {
            visit[v] = when;
            if(link[v] == -1 || find(link[v], when)) {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary(int when)
{
    int ans = 0;
    for(int i = 1; i <= n; i++) 
        ans += find(i, ++when);
    return ans;
}
void init()
{
    memset(head, -1, sizeof(head));
    memset(link, -1, sizeof(link));
    edge_num = 0;
}
int main()
{
    int when = 0, x, y, k;
    while(scanf("%d%d", &n, &m) != EOF) { 
        init();
        for(x = 1; x <= n; x++) {
            scanf("%d", &k);
            while(k--) {
                scanf("%d", &y);
                add_edge(x, y);
            }
        }

        printf("%d\n", hungary(++when));
    }
    return 0;
}

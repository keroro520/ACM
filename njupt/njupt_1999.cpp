/*
差分约束
max_ans --> B <= A + c --> min_constraint --> zuiduanlu
B - A <= c
求差值最大，初始化为INF
*/
#include <stdio.h>
#include <string.h>
#define     debug   printf("!\n")
#define     INF     2139062143
#define     MAXN    1005
#define     MAXM    10005
struct Edge { int v, value, next; } edge[MAXM];
int head[MAXN], visit[MAXN], times[MAXN], dis[MAXN];
int S[MAXN];
int when = 0, edge_num, n;
void add_edge(int u, int v, int value)
{
    Edge tmp = {v, value, head[u]};
    edge[edge_num] = tmp;
    head[u] = edge_num;
    edge_num++;
}
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
bool SPFA(int s, int t, int when);
int main()
{
    int cases, x, y, z, m;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        init();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, z);
        }
        if(!SPFA(1, n, ++when)) {
            printf("Infinite\n");
        } else printf("%d\n", dis[n] - dis[1]);
    }
    return 0;
}
bool SPFA(int s, int t, int when)
{
    memset(dis, 127, sizeof(dis));
    visit[s] = when;
    dis[s] = 0;
    int S_top = 0;
    S[++S_top] = s;
    while(S_top) {
        int u = S[S_top--];
        visit[u] = -1;
        for(int k = head[u]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(dis[v] > dis[u] + edge[k].value) {
                dis[v] = dis[u] + edge[k].value;
                if(visit[v] != when) {
                    visit[v] = when;
                    S[++S_top] = v;
                }
            }
        }
    }
    return dis[t] != INF;
}

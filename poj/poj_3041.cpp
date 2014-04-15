/*
    二分图最大匹配

    题意：N*N网格，其中一些格可以放Asteroids，每个Asteroids在同一行或同一列的话会打架，问最多能放多少Asteroids？

    经典二分图最大匹配    匈牙利算法模板

    本来觉得是模板题，后来看了hdu 1045(Fire Net)后更想明白了这道题的构图：把每一行看成一个点作为二分图的X部，同理列为Y部，若有Asteroids格在(r,c)，则说明r_X与c_Y有交集，有交集就连一条边。
*/
#include <stdio.h>
#include <string.h>
#define     MAXN    505*2
#define     MAXM    10005
struct Edge { int v, next; } edge[MAXM];
int head[MAXN], link[MAXN];
bool visit[MAXN];
int n, edge_num;

int hash(int x) { return x + n; }
void init()
{
    memset(head, -1, sizeof(head));
    memset(link, -1, sizeof(link));
    edge_num = 0;
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
        if(visit[v] == false) {
            visit[v] = true;
            if(link[v] == -1 || find(link[v])) {    //若v不属于前一个匹配，或被v匹配的节点可以找到一个增广路
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int k, r, c;
    while(scanf("%d%d", &n, &k) != EOF) {
        init();
        for(int i = 0; i < k; i++) {
            scanf("%d%d", &r, &c);
            add_edge(r, hash(c));
        }
        int ans = 0;
        for(int i = 1; i<= n; i++) {
            memset(visit, false, sizeof(visit));
            ans += find(i);
        }
        printf("%d\n", ans);
    }
    return 0;
}

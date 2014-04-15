/*
    最小费用最大流  好题

    题意：给定一个n*n的方格，每个方格里有一个数，从左上角出发，只能向下走或向右走，取过的数不计算权值，问走k次能得到的最大权值和

    思路：     睡觉去了。。。好题，要补上题解
*/
#include <deque>
#include <string.h>
#include <stdio.h>
using namespace std;
#define     MAXN        5500
#define     MAXM        100000
#define     debug       printf("!\n")
class Edge {
    public : int u, v, cost, flow, next;
             Edge(int u, int v, int cost, int flow, int next) : u(u), v(v), cost(cost), flow(flow), next(next) { }
             Edge(){ }
} edge[MAXM];
int head[MAXN], pre[MAXN], dis[MAXN], visit[MAXN];
int n, K, edge_num, sink, src, when = 1;

void _add_edge(int u, int v, int cost, int flow)
{
    edge[edge_num] = Edge(u, v, cost, flow, head[u]);
    head[u] = edge_num;
    edge_num++;
}
void add_edge(int u, int v, int cost, int flow)
{
    _add_edge(u, v, cost, flow);
    _add_edge(v, u, -cost, 0);
}
void build()
{
    int num;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            scanf("%d", &num);
            int u = i*n + j, v = n*n + u;
            add_edge(u, v, num, 1);
            add_edge(u, v, 0, K-1);

            if(j < n-1) {
                add_edge(v, u+1, 0, K);
            }
            if(i < n-1) {
                add_edge(v, u+n, 0, K);
            }
        }
    src = n*n*2 , sink = src + 1;
    add_edge(src, 0, 0, K);
    add_edge(src-1, sink, 0, K);
}
void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
bool SPFA()
{
    when++;
    memset(dis, 128, sizeof(dis));
    pre[src] = -1;
    dis[src] = 0;
    visit[src] = when;
    deque<int> Q;
    Q.push_back(src);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        visit[u] = -1;
        for(int k = head[u]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(edge[k].flow > 0 && dis[v] < dis[u] + edge[k].cost) {
                dis[v] = dis[u] + edge[k].cost;
                pre[v] = k;
                if(visit[v] != when) {
                    Q.push_back(v);
                    visit[v] = when;
                }
            }
        }
    }
    return dis[sink] > 0;
}
int MCMF()
{
    int ans = 0;
    while(SPFA()) {
        for(int k = pre[sink]; k != -1; k = pre[edge[k].u]) {
            edge[k].flow--; 
            edge[k^1].flow++;
        }
        ans += dis[sink];
    }
    return ans;
}
int main()
{
    while(scanf("%d%d", &n, &K) != EOF) {
        init();
        build();
        printf("%d\n", MCMF());
    }
    return 0;
}

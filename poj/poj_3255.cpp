/*
    次最短路（边可允许重复走）   好题
    题意：无向图，求次最短路，边可重复走

    摘：https://www.byvoid.com/blog/pku-3255/
    这道题不同于一般的次短路径问题，因为允许边重走。看似更为复杂了，其实是更简单了一些。方
    法为先用Heap+Dijkstra求出1和N的单源最短路径，把无向边看成两个有向边，然后枚举每单向条边
    (u,v)，计算Dist=dis(1,u) + dis(N,v) + w，看看此时Dist的值是否大于dis(1,N)，如果是的话用
    它更新次短路径，保留一个最小的值。

    我画了一下图，如果边e(u,v,w)在次最短路，那么情况无非3种：
    (1) e不在最短路上，且u,v也不在最短路上，则Dist=dis(1,u) + dis(N,v) + w很显然使用（可以
        看成最短与次短就是两条有岔口的路径
    (2) e不在最短路上，u,v有一点在最短路上，则Dist=dis(1,u) + dis(N,v) + w就等于最短路长度
        shortest + 2*w
    (3) e在最短路上，则Dist=dis(1,u) + dis(N,v) + w大于shortest的话，其实就是s->u->v->u->v->t

    由于AC后发现自己的dijstra不是堆优化的=_=弄混了，应该是pair<dis, node>的，写成pair<node,pair>
    了=_=，所以干脆删掉了
*/
int solve()
{
    dijstra(1, n, sp[0]), dijstra(n, 1, sp[1]);
    int short_path = sp[0][n], ans = INF;
    for(int i = 0; i < edge_num; i++) {
      u = edge[i].u, v = edge[i].v, w = edge[i].w;
      int tmp = sp[0][u] + sp[1][v] + w;
      if(tmp > short_path && ans > tmp) ans = tmp;
    }
    return ans;
}




#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <queue>
using namespace std;
#define MAXN 5005
#define INF  999999999
#define MAXM 100005
typedef pair<int,int> Pii;
priority_queue< Pii > Q;
struct Edge {
  int u, v, w, next;
} edge[MAXM * 2];
int head[MAXN], sp[2][MAXN];

int main()
{
  int m, u, w, v;
  while(scanf("%d%d", &n, &m) != EOF) {
    init();
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w), add_edge(v, u, w);
    }

    printf("%d\n", solve());
  }
  return 0;
}
int n, edge_num;
void init()
{
  memset(head, -1, sizeof(head));
  edge_num = 0;
}
void add_edge(int u, int v, int w)
{
  edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w;
  edge[edge_num].next = head[u]; head[u] = edge_num++;
}

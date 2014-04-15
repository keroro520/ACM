/*
  最优比率环
  http://www.cnblogs.com/wally/p/3228171.html
*/
#include <algorithm>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
#define   INF     (1.0*(1<<30))
#define   MAXN    1111
#define   EPS     1e-4
struct Edge {
  int v, next; double w;
} edge[MAXN*10];
int head[MAXN], cnt[MAXN], vis[MAXN];
double dis[MAXN], node[MAXN];
int n, m, edge_num, when;
void add_edge(int u, int v, double w) {
  edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
  head[u] = edge_num++;
}
bool SPFA(double r, int s)
{
  for(int i = 1; i <= n; i++) cnt[i] = 0, dis[i] = INF;
  dis[s] = 0;
  queue<int> Q;
  Q.push( s );
  while(!Q.empty()) {
    int u = Q.front(); Q.pop();
    vis[u] = 0;
    if(++cnt[u] > n) return true; //有负环

    for(int k = head[u]; k != -1; k = edge[k].next) {
      int v = edge[k].v; double tmp = edge[k].w * r - node[u];
      if(dis[u] + tmp < dis[v]) {
        dis[v] = dis[u] + tmp;
        if(vis[v] != when) vis[v] = when, Q.push(v);
      }
    }
  }
  return false;
}
int main()
{
  freopen("in.txt","r",stdin);
  int u, v; double w;
  while( scanf("%d%d", &n, &m) != EOF ) {
    edge_num = 0, memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; i++) scanf("%lf", &node[i]);
    for(int i = 0; i < m;  i++) {
      scanf("%d%d%lf", &u, &v, &w);
      add_edge(u, v, w);
    }
    double l = 0, r = 10000, mid, ans = 0;
    while(r - l > EPS) {
      mid = (l + r) / 2;
      when++;
      if(SPFA(mid, 1)) ans = l = mid; else r = mid;
    }
    printf("%.2f\n", ans);
  }
  return 0;
}

/*
思路：之前做过最小比率生成树，也是属于0/1整数划分问题，这次碰到这道最优比率环，很是熟悉，可惜精度没控制好，要不就是wa,要不就是tle，郁闷啊！实在是懒得码字，直接copy吧：

题目的意思是：求一个环的{点权和}除以{边权和}，使得那个环在所有环中{点权和}除以{边权和}最大。
令在一个环里，点权为v[i]，对应的边权为e[i]， 
即要求：∑（i=1，n）v[i]/∑（i=1，n)e[i]最大的环（n为环的点数）， 
设题目答案为ans， 
即对于所有的环都有 ∑（i=1，n）（v[i]）/∑（i=1，n)（e[i]）<=ans 
变形得ans* ∑（i=1，n）（e[i]）>=∑（i=1，n）（v[i]） 
再得 ∑（i=1，n）（ans*e[i]-v[i]） >=0 
稍分析一下，就有： 
当k<ans时，就存在至少一个环∑（i=1，n）（k*e[i]-v[i]）<0，即有负权回路(边权为k*e[i]-v[i])； 
当k>=ans时，就对于所有的环∑（i=1，n）（k*e[i]-v[i]）>=0，即没有负权回路。 
然后我们就可以使新的边权为k*e[i]-v[i]，用spfa来判断付权回路,二分ans。
*/

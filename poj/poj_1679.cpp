/*
  判断一个图的最小生成树是否唯一
  题意：判断一个图的最小生成树是否唯一

  思路：判断一个图的最小生成树是否唯一，可以求其次小生成树。如果它的次小生成树权值之和等于最小生成树权值之和，则最小生成树不唯一，否则最小生成树唯一。

求次小生成树我的方法是O(N^2 + M)的。首先求出最小生成树，记录权值之和为MinST。然后枚举添加边(u,v)，加上以后一定形成一个环，找到环上非(u,v)边的权值最大的边，把它删掉，计算当前生成树的权值之和，取所有枚举加边后生成树权值之和的最小值，就是次小生成树。

实际上具体更简单的方法为从每个顶点i，遍历整个最小生成树，定义F[j]为从i到j的路径上最大边的权值，用O(N)的方法求出每个F[j]。然后枚举顶点i的邻域，遍历每条不再最小生成树中的边(i,j)，加上这条边，并删除环上最大边(非(i,j))，新的生成树权值之和为MinST + w(i,j) - F[j]，记录其最小值即可，时间复杂度为O(N^2 + M)。求最小生成树可以用最简单的Prim，时间复杂度为O(N^2)，用更好的算法是没有意义的。

这种方法比起那种求出最小生成树后，枚举删除最小生成树上每条边，然后再求最小生成树的方法应该要快些，因为那种方法的时间复杂度为O(N ( N logN + M) )(Prim + Heap)。


    本来想写得优美一点的，谁知道越写越臃肿 =_= 看上面摘抄的分析就可以了，别看代码=_=
*/
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <algorithm>
#include <functional>
using namespace std;
#define MAXN 105
#define MAXM 105*105
typedef pair<int,int> Pii;
struct Edge {
  int u, v, w, next;
} edge[MAXM];
bool vis[MAXN], used[MAXM];
vector<Pii> adj[MAXN];
priority_queue< pair<Pii, int> , vector< pair<Pii, int> >, greater< pair<Pii, int> > > Q;
int head[MAXN], dis[MAXN];
int n, m, edge_num, mst, INF;

void add_edge(int u, int v, int w) {
  edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w;
  edge[edge_num].next = head[u]; head[u] = edge_num++;
}
void init()
{
  edge_num = 0; memset(head, -1, sizeof(head));
}
void input()
{
  int u, v, w;
  scanf("%d%d", &n, &m);
  init();
  for(int i = 0; i < m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    add_edge(u, v, w), add_edge(v, u, w);
  }
}
void dfs(int u, int pre, int d)
{
  dis[u] = d;
  for(vector<Pii> :: iterator it = adj[u].begin(); it != adj[u].end(); it++)
    if(it->first != pre) dfs(it->first, u, max(d, it->second));
}
void prim(int s)
{
  memset(used, false, sizeof(used));
  memset(dis, 127, sizeof(dis));
  memset(vis, false, sizeof(vis));
  for(int i = 1; i <= n; i++) adj[i].clear();
  while( !Q.empty() ) Q.pop();
  Q.push( pair<Pii, int>(Pii(0, -1), s) );
  dis[s] = 0;
  while( !Q.empty() ) {
    int u = Q.top().second; int tk = Q.top().first.second; Q.pop();
    if(vis[u]) continue; else vis[u] = true;

    if(tk != -1) {
      adj[u].push_back( Pii(edge[tk].u, edge[tk].w) );
      adj[edge[tk].u].push_back( Pii(u, edge[tk].w) );
      used[tk] = used[tk^1] = true;
    }
    for(int k = head[u]; k != -1; k = edge[k].next) {
      int v = edge[k].v, w = edge[k].w;
      if(!vis[v] && dis[v] > w) dis[v] = w, Q.push( pair<Pii,int>(Pii(w, k), v) );
    }
  }
  mst = 0;
  for(int i = 1; i <= n; i++) mst += dis[i];
}
bool solve()
{
  prim(1);
  for(int i = 1; i <= n; i++) if(dis[i] == INF) { mst = 0; return true; }
  int ans = INF;
  for(int i = 1; i <= n; i++) {
    dfs(i, i, 1);
    for(int k = head[i]; k != -1; k = edge[k].next) if(!used[k]) {
      int v = edge[k].v, w = edge[k].w;
      ans = min(ans, mst + w - dis[v]);
    }
  }
  return ans != mst;
}
int main()
{
  int cases;
  memset(&INF, 127, sizeof(INF));
  scanf("%d", &cases);
  while(cases--) {
    input();
    if(n == 1) puts("0");
    else if(!solve()) puts("Not Unique!");
    else printf("%d\n", mst);
  }
  return 0;
}

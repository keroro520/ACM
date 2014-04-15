/*
  最短路变一下而已
  用栈死活TLE，用队列就过了，囧。。。
*/

#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <deque>
using namespace std;
#define MAXN 100005
typedef long long ll;
struct Edge {
  int v, w, next;
} edge[MAXN * 2];
struct Interval {
  ll s, t;
  Interval(ll s, ll t) : s(s), t(t) {}
} ;
deque<int> Q;
int head[MAXN], S[MAXN];
ll dis[MAXN];
ll INF;
bool in_stack[MAXN];
vector<Interval> interval[MAXN];
int edge_num, n;
void add_edge(int u, int v, int w)
{
  edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
  head[u] = edge_num++;
}
int __Find(int u, ll w)
{
  int l = 0, r = interval[u].size()-1, mid, ans;
  while(l <= r) {
    mid = (l+r)/2;
    if(interval[u][mid].t >= w) ans = mid, r = mid-1;
    else l = mid + 1;
  }
  return ans;
}
int Find(int u, ll w)
{
  int p = __Find(u, w);
  return max(w, interval[u][p].s);
//  if(w <= interval[u][0].s) return interval[u][0].s;
//  for(int i = 0; i < interval[u].size(); i++)
//    if(interval[u][i].s <= w && w <= interval[u][i].t) return w;
//    else if(w < interval[u][i+1].s) return interval[u][i+1].s;
}

ll SPFA(int s)
{
  ll ans = INF;
  int S_top = 0;
  memset(in_stack, false, sizeof(in_stack));
  memset(dis, 127, sizeof(dis));
//  S[S_top++] = s;
  Q.push_back(s);
  dis[s] = Find(s, 0);
  while(!Q.empty()) {
//  while(S_top) {
//    int u = S[--S_top];
//    in_stack[u] = false;
    int u = Q.front(); Q.pop_front();in_stack[u] = false;
    if(u == n) ans = min(ans, dis[n]);
    ll www = Find(u, dis[u]);
    dis[u] = www;
    for(int k = head[u]; k != -1; k = edge[k].next) {
      int v = edge[k].v, w = edge[k].w;
      if(dis[v] > www + w) {
          dis[v] = www + w;
          if(!in_stack[v]) in_stack[v] = true, Q.push_back(v);//S[S_top++] = v, in_stack[v] = true;
      }
    }
  }
  return ans == INF ? -1 : ans;
}
int main()
{
 // freopen("in.txt","r",stdin);
  memset(&INF, 127, sizeof(ll));
  int m, u, v, w;
  memset(head, -1, sizeof(head));
  scanf("%d%d", &n, &m);
  while(m--) {
    scanf("%d%d%d", &u, &v, &w);
    add_edge(u, v, w), add_edge(v, u, w);
  }
  for(int i = 1; i <= n; i++) {
    int st = 0, x = 0, k;
    scanf("%d", &k);
    while(k--) {
      scanf("%d", &x);
      if(x == st) st++;
      else interval[i].push_back( Interval(st, x-1) ), st = x + 1;
    }
    interval[i].push_back( Interval((ll)st, INF) );
  }

  printf("%I64d\n", SPFA(1));
  return 0;
}

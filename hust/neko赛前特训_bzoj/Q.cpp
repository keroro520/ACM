#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#define MAXN 1000005
typedef long long ll;
struct Edge {
  int v, next,w;
} edge[MAXN*2];
ll len[MAXN];
int child[MAXN], head[MAXN];
int n, edge_num;

void add_edge(int u, int v, int w)
{
  edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
  head[u] = edge_num++;
}
void dfs(int u, int pre, int dd)
{
  child[u] = 1;
  len[u] = dd;
  for(int k = head[u]; k != -1; k = edge[k].next) {
    int v = edge[k].v, w = edge[k].w;
    if(v == pre)  continue;
    dfs(v, u, w);
    child[u] += child[v];
  }
}
int main()
{
  int u,v, w;
  scanf("%d", &n);
  memset(head, -1, sizeof(head));
  for(int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    add_edge(u, v, w), add_edge(v, u, w);
  }
  dfs(1, 1, 0);
  child[1] = len[1] = 0;
  ll ans = 0;
  for(int i = 2; i <= n; i++) ans += (ll)len[i] * abs(child[i] - (n-child[i]));
 // for(int i = 1; i <= n; i++) printf("! %d %d  %d \n", i, child[i], len[i], len[i]*child[i]);
  cout << ans << endl;
  return 0;
}

/*
  好题等题解
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 1000005
#define MAXM 1000005
struct Edge {
  int v, next;
} edge[MAXM*2];
int n, edge_num, when;
int head[MAXN], vis[MAXN], link[MAXN];

void add_edge(int u, int v)
{
  edge[edge_num].v = v, edge[edge_num].next = head[u];
  head[u] = edge_num++;
}
bool find(int u)
{
  for(int k = head[u]; k != -1; k = edge[k].next) {
    int v = edge[k].v;
    if(vis[v] == when) continue;
    vis[v] = when;
    if(link[v] == -1 || find(link[v])) {
      link[v] = u;
      return true;
    }
  }
  return false;
}

int hungary()
{
  memset(link, -1, sizeof(link));
  for(int i = 1; i <= n; i++) {
    when++;
    if(!find(i)) return i-1;
  }
  return n;
}
int main()
{
  int x, y;
  memset(head, -1, sizeof(head));
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &x, &y);
    add_edge(x, i), add_edge(y, i);
  }
  printf("%d\n", hungary());
  return 0;
}

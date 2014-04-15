/*
	好题  等题解
*/
#include <stdio.h>
#include <string.h>
#define MAXN 305
#define INF  999999999
int n, path[MAXN][MAXN], dis[MAXN];
bool vis[MAXN];
int prim(int s)
{
  for(int i = 0; i <= n; i++) dis[i] = INF, vis[i] = false;
  dis[s] = 0;
  int mst = 0;
  for(int k = 0; k <= n; k++) {
    int _min = INF, _min_i = -1;
    for(int i = 0; i <= n; i++) if(!vis[i] && dis[i] < _min) {
      _min = dis[i], _min_i = i;
    }
    vis[_min_i] = true, mst += _min;
    for(int i = 0; i <= n; i++) if(!vis[i] && path[_min_i][i] < dis[i]) {
      dis[i] = path[_min_i][i];
    }
  }
  return mst;
}
int main()
{
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) scanf("%d", &path[0][i]);
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++) scanf("%d", &path[i][j]);
  printf("%d\n", prim(0));
  return 0;
}

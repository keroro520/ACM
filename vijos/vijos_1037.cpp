/*
  DP  背包  搭建双塔
  题意：N块水晶的高度Hi，判断能否用这些水晶搭建成一座有同样的高度的双塔，如果能，则输出所能
        搭建的双塔的最大高度，否则输出“Impossible”。

  思路：判定性问题
        f[j][k]表第一座塔高为j，第二座塔高为k是否可能
        f[j][k] = f[j-a[i]][k] || f[j][k-a[i]]
        讨论里有人用二分过，应该是二分+背包判定吧

        要加sort和min(sum,m)优化，不然会超时
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAXN 2005
int n, a[MAXN];
bool f[MAXN][MAXN];
int main()
{
  scanf("%d", &n);
  int m = 0;
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  sort(a, a+n);
  f[0][0] = true;

  //M
  for(int i = 0; i < n; i++) {
    m += a[i];
    for(int j = min(m, M); j >= c[i]; j--)
      for(int k = m; k >= 0; k--) if(!f[j][k]) {
        if(j >= a[i] && f[j-a[i]][k]) f[j][k] = true;
        if(k >= a[i] && f[j][k-a[i]]) f[j][k] = true;
      }
  }
  int ans = -1;
  for(int j = m; j > 0; j--) if(f[j][j]) { ans = j; break; }
  if(ans == -1) puts("Impossible"); else printf("%d\n", ans);
  return 0;
}

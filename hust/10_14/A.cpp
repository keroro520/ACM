#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAXN 2005
typedef long long ll;
int n, t[MAXN];
ll c[MAXN], f[MAXN][MAXN], INF;
int main()
{
  freopen("in.txt","r",stdin);
  memset(&INF, 128, sizeof(ll));
  ll sum_cost = 0;
  int sum_time = 0;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d%I64d", &t[i], &c[i]);
    sum_time =  max(sum_time, t[i]);
    sum_cost += c[i];
  }
  memset(f, 128, sizeof(f));
  f[0][0] = 0;
  for(int i = 1; i <= n; i++) {
    for(int j = sum_time; j >= 0; j--) {
      f[i][j] = f[i-1][j-t[i]] ;
      if(f[i-1][j+1] != INF) f[i][j] = max(f[i][j], f[i-1][j+1] + c[i]),printf("## %I64d\n", f[i][j]);
    }
  }
  printf("! %I64d\n", f[2][1]);
  ll ans = -INF;
  for(int j = sum_time; j >= 0; j--) ans = min(ans, sum_cost-f[n][j]);
  printf("%I64d\n", ans);
  return 0;
}

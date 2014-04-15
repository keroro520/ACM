#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 10005
int n, L, R, Ql, Qr;
int a[MAXN], sum[MAXN];
int solve(int i)
{
  int ans = sum[i] * L + (sum[n] - sum[i]) * R;
  if(i > n-i) ans += (sum[i] - sum[n-i+1]) * Ql;
  else        ans += (sum[n-i] - sum[i]) * Qr;
  return ans;
}
int main()
{
  freopen("in.txt","r",stdin);
  scanf("%d%d%d%d%d", &n, &L, &R, &Ql, &Qr);
  for(int i = 1; i <= n; i++) scanf("%d", &a[i]), sum[i] = sum[i-1] + a[i];

  int ans = 999999999;
  for(int mid = 0; mid <= n; mid ++) ans = min(ans, solve(mid));    //ÏÂÏÞ×¢Òâ
  printf("%d\n", ans);
  return 0;
}

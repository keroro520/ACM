/*
  单调栈
  用单调栈写1A了，可以并查集始终WA！

*/
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MAXN 100100
ll a[MAXN], sum[MAXN];
int left[MAXN], right[MAXN], S[MAXN], n;
ll solve()
{
  int top = 0;
  for(int i = 1; i <= n; i++) {
    while(top && a[S[top-1]] >= a[i]) top--;
    left[i] = top ? S[top-1] : 0;
    S[top++] = i;
  }
  top = 0;
  for(int i = n; i >= 1; i--) {
    while(top && a[S[top-1]] >= a[i]) top--;
    right[i] = top ? S[top-1] : n+1;
    S[top++] = i;
  }
  ll ans = 0;
  for(int i = 1; i <= n; i++) ans = max(ans, (sum[right[i]-1] - sum[left[i]])*a[i]);
  return ans;
}
int main()
{
 // freopen("in.txt","r",stdin);
  while(scanf("%d", &n) != EOF) {
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum[i] = sum[i-1] + a[i];
    printf("%lld\n", solve());
  }
  return 0;
}

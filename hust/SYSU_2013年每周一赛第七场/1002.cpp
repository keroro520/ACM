#include <stdio.h>
#include <iostream>
using namespace std;
#define INF  (1LL << 60)
#define MAXN 100005
typedef long long ll;
int T[MAXN];
int n, m;
bool check(ll sec)
{
  ll sum = 0;
  for(int i = 0; i < n; i++) {
    sum += sec / T[i];
  }
  return sum >= m;
}
int main()
{
  while(scanf("%d%d", &n, &m) != EOF) {
    for(int i = 0; i < n; i++) scanf("%d", &T[i]);
    ll r = INF, l = 0, ans = 0, mid;
    while(l <= r) {
      mid = (l + r) / 2LL;
      if(check(mid)) ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    cout << ans << endl;
  }
  return 0;
}

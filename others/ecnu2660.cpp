//WA
// 并查集做法，TLE我能接受，可是到现在都不知道为什么WA.
// 可是感觉我的算法没错呀。。郁闷，求助了fubaogg
//http://202.120.80.191/problem.php?problemid=2660

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define MAXN 1000005
typedef long long  ll;
int n;
ll a[MAXN], sum[MAXN];
int after[MAXN], front[MAXN];
int Find(ll x, int i, int * p)
{
  while(p[i] != i) {
    if(x <= a[i]) i = p[i]; else return i;
  }
  //while(a[i] >= x) i = p[i];
  return i;
}
int main()
{
   // freopen("in.txt","r",stdin);
  while(scanf("%d", &n) != EOF) {
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), sum[i] = sum[i-1] + a[i];
    a[0] = a[n+1] = -999999999; front[0] = 0, after[n+1] = n+1;
    //for(int i = 1; i <= n; i++) after[i] = n+1, front[i] = 0;
    for(int i = 1; i <= n; i++)
      if(a[i] > a[i-1]) front[i] = i-1;
      else front[i] = Find(a[i], i-1, front);

    for(int i = n; i >= 1; i--)
      if(a[i] > a[i+1]) after[i] = i+1;
      else after[i] = Find(a[i], i+1, after);

    ll ans = 0;
    //for(int i = 1; i <= n; i++) printf("a[%d] = %lld     %d  %d\n",i,a[i], front[i], after[i]);
    for(int i = 1; i <= n; i++)
      ans = max(ans, (sum[ after[i]-1 ] - sum[front[i]]) * a[i]);
    cout << ans << endl;
  }
  return 0;
}

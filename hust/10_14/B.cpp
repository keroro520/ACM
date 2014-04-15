#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
typedef long long ll;
#define EPS 1e-8
double l, v1, v2, T;
int dblcmp(double x) {
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
}
double calc_same(int step, int p, int q, double fuck)
{
  while(true) {
    double t1 = p*l/v1, t2 = (fuck + q*l)/v2;
    if(dblcmp(t1-T) > 0 || dblcmp(t2-T) > 0) break;
    if(dblcmp(t2) && dblcmp(t1 - t2) == 0) return t2;
    else if(dblcmp(t1-t2) >= 0) q += step;
    else p += step;
  }
  return T + 10;
}

int main()
{
  scanf("%lf%lf%lf%lf", &l, &v1, &v2, &T);
  if(v1 > v2) swap(v1, v2);
  ll ans = 0;
  double t1 = l/(v1+v2);
  ans += (ll)((T/t1+1)/2);
  ans += (ll)((T*(v2-v1)/l+1)/2);
  double meet = calc_same(1, 0, 0, l);
  if(meet <= T) {
    ans --;
    T -= meet;
    meet = calc_same(1, 0, 0, 0); //printf("!! %lf\n", meet);
    if(T >= meet) ans -= (ll)(T / meet);
  }
  printf("%lld\n", ans);
  return 0;
}

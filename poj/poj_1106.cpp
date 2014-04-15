/*
  解析几何  圆心确定的半圆最多能覆盖的点数
  给定一些点，和一个圆心坐标，求一个半圆能最多能圈下多少点。

  思路：枚举半圆一端边的位置 + 叉积判断
*/
#include <math.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define MAXN 205
class Point {
  public : double x, y;
} p[MAXN];
double _dis(const Point &a, const Point &b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
#define EPS 1e-8
int dblcmp(double x) {
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
}
double xmulti(const Point &a, const Point &b, const Point & c)
{
  return (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x);
}
int n;
int main()
{
  Point C;
  double R;
  while(scanf("%lf%lf%lf", &C.x, &C.y, &R), R > 0) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
    int ans = 0;
    for(int i = 0; i < n; i++) if(_dis(p[i], C) <= R) {
      int tot = 0;
      for(int j = 0; j < n; j++) tot += ( _dis(p[j], C) <= R && dblcmp(xmulti(p[i], p[j], C)) >= 0);
      ans = max(ans, tot);
    }
    printf("%d\n", ans);
  }
  return 0;
}

/*
  解析几何 过一点求圆切线 极角
  题目：给出一个光源，给出一些圆，求投影区间。

  思路：切线，解析几何搞搞
        asin, atan...不用呈上180/Pi...
        http://blog.csdn.net/acm_cxlove/article/details/7896110
*/
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;
#define MAXN 505
class Point { public : double x, y; };
class Line  {
  public : double l, r;
  friend bool operator < (const Line &a, const Line &b) {
    if(a.l != b.l) return a.l < b.l;
    return a.r < b.r;
  }
} line[MAXN];
inline double _dis(const Point &a, const Point &b)
{
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
int main()
{
  int n;
  Point c, base;
  double R;
  while(scanf("%d", &n) != EOF && n) {
    scanf("%lf%lf", &base.x, &base.y);
    for(int i = 0; i < n; i++) {
      scanf("%lf%lf%lf", &c.x, &c.y, &R);
      double d = _dis(base, c);
      double angle_A = asin(R/d);
      double angle_B = asin((base.x-c.x)/d);

      line[i].l = base.x - tan(angle_A + angle_B)*base.y;
      line[i].r = base.x - tan(angle_B - angle_A)*base.y;
    }
    sort(line, line+n);
    int tot = 0;
    for(int i = 1; i < n; i++)
      if(line[i].l > line[tot].r) line[++tot] = line[i];
      else line[tot].r = max(line[tot].r, line[i].r);
    for(int i = 0; i <= tot; i++) printf("%.2f %.2f\n", line[i].l, line[i].r);
    puts("");
  }
  return 0;
}

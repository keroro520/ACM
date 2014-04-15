/*
  计算几何  半平面交 + 二分 + 向内推进  多边形内切圆  好题

  题意：求多边形内切圆的半径

  思路：二分半径R
        将多边形每条边内推R，然后看看是否存在半平面交，如果
        存在的话我们就可以将圆心放在该半平面交里面，




  一直WA ， 小数据对拍了好久都没错。
  后来做poj_3384的时候突然想到，半平面交的点集必须要是有序的
  可是我在cut()函数里面把下面两句顺序弄反了，然后就悲剧了=_=
    if(A*hpi[i-1].x + B*hpi[i-1].y + C > 0)
    if(A*hpi[i+1].x + B*hpi[i+1].y + C > 0)

  二分忘记初始化ans =_= 该打！


*/
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define MAXN  205
#define EPS  1e-11
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
} p[MAXN], hpi[MAXN], q[MAXN];

int n, cnt_hpi;
double A, B, C;
int dblcmp(double x)
{
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
}
Point intersection(const Point &a, const Point &b, double A, double B, double C)
{
  double u = fabs(A * a.x + B * a.y + C);
  double v = fabs(A * b.x + B * b.y + C);
  return Point( (v*a.x + u*b.x)/(u+v),
                (v*a.y + u*b.y)/(u+v) );
}
void init_HPI()
{
  cnt_hpi = n;
  for(int i = 0; i <= n+1; i++) hpi[i] = p[i];
}
void getline(const Point &a, const Point &b)
{
  A = b.y - a.y;
  B = a.x - b.x;
  C = b.x*a.y - a.x*b.y;
}
void cut()
{
  int m = 0;
  for(int i = 1; i <= cnt_hpi; i++) {
    if(A*hpi[i].x + B*hpi[i].y + C >= 0) q[++m] = hpi[i];
    else {
      if(A*hpi[i-1].x + B*hpi[i-1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i-1], A, B, C);
      if(A*hpi[i+1].x + B*hpi[i+1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i+1], A, B, C);
    }
  }
  cnt_hpi = m;
  for(int i = 1; i <= m; i++) hpi[i] = q[i];
  hpi[0] = hpi[m], hpi[m+1] = hpi[1];
}
bool HPI(double R)
{
  init_HPI();
  //向内推进R
  for(int i = 1; i <= n; i++) {
    double tx = p[i+1].y - p[i].y;
    double ty = p[i].x - p[i+1].x;
    double slope = R / sqrt(tx*tx + ty*ty);
    ty = ty * slope, tx = tx * slope;

    Point a(p[i].x + tx, p[i].y + ty);
    Point b(p[i+1].x + tx, p[i+1].y + ty);

    getline(a, b);
    cut();
  }
  return cnt_hpi > 0;
}
int main()
{
  while(scanf("%d", &n) != EOF && n) {
    for(int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);

    reverse(p+1, p+n+1);
    p[0] = p[n], p[n+1] = p[1];

    double l = 0, r = 1e9, mid, ans = 0;
    while( l + EPS < r ) {
      mid = (l + r)/2;
      if(HPI(mid)) l = ans = mid;
      else r = mid;
    }
    printf("%lf\n", ans);
  }
  return 0;
}

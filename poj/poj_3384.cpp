/*
  计算几何 半平面交 向内推进
  题意: 在多边形内安排两个半径为R的圆，两个圆范围不能超过多边形（即不能相交，可以内
        切）使得两个圆覆盖的区域尽可能大（重合的部分只算一次），求两个圆的圆心坐标。

  思路：先向内推进R，然后求半平面交（题目保证存在），然后在半平面交里找到两个距离
        最远的点，用这两个点做圆心最优。
        取圆心在内推后的多边形的半平面交，能够保证圆不超过多边形。而取半平面交上的两个
        最远的点，即两个圆的圆心距最大，使得两个圆重合的部分尽量小。那为什么两个最远
        的点会在半平面交的顶点上？因为半平面交是个凸多边形，而凸多边形里两个最远的点
        一定在顶点上。
*/
#include <stdio.h>
#include <math.h>
#define MAXN 1005
#define EPS  1e-8
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
  friend Point operator + (const Point &a, const Point &b) {
    return Point(a.x+b.x, a.y+b.y);
  }
} a[MAXN], hpi[MAXN], q[MAXN];
int n, cnt_hpi;
double A, B, C;
double _dis(const Point &a, const Point &b)
{
#define SQR(x)    ((x)*(x))
  return sqrt( SQR(a.x-b.x) + SQR(a.y-b.y) );
}
void init_HPI()
{
  cnt_hpi = n;
  for(int i = 0; i <= n+1; i++) hpi[i] = a[i];
}
void get_line(const Point &a, const Point &b)
{
  A = b.y - a.y;
  B = a.x - b.x;
  C = b.x*a.y - b.y*a.x;
}
Point intersection(const Point &a, const Point &b, double A, double B, double C)
{
  double u = fabs(A * a.x + B * a.y + C);
  double v = fabs(A * b.x + B * b.y + C);
  return Point( (v*a.x + u*b.x)/(u+v),
                (v*a.y + u*b.y)/(u+v) );
}
void cut()
{
  int m = 0;
  for(int i = 1; i <= cnt_hpi; i++) {
    if(A*hpi[i].x + B*hpi[i].y + C >= 0) {
      q[++m] = hpi[i];
    } else {
      if(A*hpi[i-1].x + B*hpi[i-1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i-1],A, B, C);
      if(A*hpi[i+1].x + B*hpi[i+1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i+1],A, B, C);
    }
  }
  cnt_hpi = m;
  for(int i = 1; i <= m; i++) hpi[i] = q[i];
  hpi[0] = hpi[m], hpi[m+1] = hpi[1];
}
void HPI(double R)
{
  init_HPI();
  for(int i = 1; i <= n; i++) {
    Point t;
    t.x = a[i+1].y - a[i].y;
    t.y = a[i].x - a[i+1].x;
    double k  = R / sqrt(t.x*t.x + t.y*t.y);
    t.x *= k, t.y *= k;
    Point p1(a[i] + t), p2(a[i+1] + t);
    //printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", a[i].x,a[i].y,p1.x,p1.y);
    //printf("(%.2f, %.2f) -> (%.2f, %.2f)\n", a[i+1].x,a[i+1].y,p2.x,p2.y);
    get_line(p1, p2);
    cut();
  }
}
bool Find_Farest_2points(Point &p1, Point &p2)
{
  double max_dis = -EPS;
  for(int i = 1; i <= cnt_hpi; i++)
    for(int j = 1; j <= cnt_hpi; j++) {
      double tmp = _dis(hpi[i], hpi[j]);
      if(tmp > max_dis) {
        max_dis = tmp;
        p1 = hpi[i], p2 = hpi[j];
      }
    }
  return cnt_hpi > 0;
}
int main()
{
  freopen("in.txt","r",stdin);
  double R;
  while(scanf("%d%lf", &n, &R) != EOF) {
    for(int i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    a[0] = a[n], a[n+1] = a[1];

    HPI(R);
    Point p1(0,0), p2(0,0);
    Find_Farest_2points(p1, p2);
    printf("%.4f %.4f %.4f %.4f\n", p1.x,p1.y,p2.x,p2.y);
  }
  return 0;
}

/*
  计算几何 半平面交
  题意：判断是否存在半平面交，点已经按顺时针序给出

  思路：hpi存半平面交点集，cnt_HPI记录个数
        A, B, C是线性方程A*x + B*y + C = 0的参数

        本来想找lrj说的为了应付无限区间，先确定4个大端点的模板的，没找到合适的，先这样吧

        这道题因为半平面交可能很小，甚至为一个点，所以不能用判断面积法判平面交


        之前我要操作连续两个点的话(如叉积，面积)都是p[i],p[(i+1)%n](下标从0开始，这里有另外一种方法是
        下标从1开始，p[0] = p[n]，p[n+1] = p[1]，然后就不用每次都模了，好方便
*/
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define MAXN 1505
#define EPS  1e-8
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) { }
} p[MAXN], q[MAXN], hpi[MAXN];
int n, cnt_HPI;
double A, B, C;

double xmulti(const Point &a, const Point &b)
{
  return a.x*b.y - b.x*a.y;
}
double Area(const Point *p, int n)
{
  double area = 0.0;
  for(int i = 1; i <= n; i++) area += xmulti(p[i], p[i+1]);
  return area;
}
void init_HPI()
{
  cnt_HPI = n;
  for(int i = 0; i <= cnt_HPI+1; i++) hpi[i] = p[i];
}

Point intersection(const Point &a, const Point &b)
{
  double u = fabs( A*a.x + B*a.y + C);
  double v = fabs( A*b.x + B*b.y + C);
  return Point( (a.x*v + b.x*u)/(u+v), (a.y*v + b.y*u)/(u+v) );
}
void build_line(const Point &a, const Point &b)
{
  A = b.y - a.y;
  B = a.x - b.x;
  C = b.x * a.y - a.x * b.y;
}

void cut()
{
  int m = 0;
  for(int i = 1; i <= cnt_HPI; i++) {
    if(A*hpi[i].x + B*hpi[i].y + C >= 0)
      q[++m] = hpi[i];
    else {
      if(A*hpi[i-1].x + B*hpi[i-1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i-1]);
      if(A*hpi[i+1].x + B*hpi[i+1].y + C > 0)
        q[++m] = intersection(hpi[i], hpi[i+1]);
    }
  }

  cnt_HPI = m;
  for(int i = 1; i <= m; i++) hpi[i] = q[i];
  hpi[0] = hpi[m], hpi[m+1] = hpi[1];
}
double HPI()
{
  init_HPI();

  for(int i = 1; i <= n; i++) {
    build_line(p[i], p[i+1]);
    cut();
    if(i != 1) continue;
  }

  //return cnt_HPI >= 1;
  double area  = Area(hpi, cnt_HPI);
  return fabs(area/2);
}
int main()
{
  int cases;
//  freopen("in.txt","r",stdin);
scanf("%d", &cases);
while(cases--) {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
    //if(anticlock())
      //reverse(p+1, p+n+1);
    p[0] = p[n], p[n+1] = p[1];

    printf("%.2f\n", HPI());
  }
  return 0;
}

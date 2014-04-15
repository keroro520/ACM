/*
  计算几何  半平面交  中垂线   好题
  题意：一个(0,0),(10,10)的矩形，一个目标物体在这里面某个点。一个人从(0,0)开始遍历某些点找目标物体
        没到达一个新的点，就会有提示新点距离目标点是比前一个点近了还是远了。问每一次到达一个新的点
        后能够确定目标物体可能在的面积大小

  思路：虽说是做半平面交专题，但是说实话看到这道题还是没什么思路。看到题解说用中垂线，恍然大悟，1Y
        到达一个新的点，远或近的提示不就是说目标点在两点连线的中垂线的左边还是右边吗。

        初始可行区间为(0,0),(10,10)，接下来不断用相邻两点的中垂线切分可行区间。
        学到了求中垂线
*/
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define EPS 1e-10
#define MAXN 1000

int dblcmp(double x)
{
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
}
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
  friend bool operator == (const Point &a, const Point &b) {
    return dblcmp(a.x-b.x) == 0 && dblcmp(a.y-b.y) == 0;
  }
  friend Point operator * (const Point &a, const double &k) {
    return Point(a.x*k, a.y*k);
  }
  friend Point operator + (const Point &a, const Point &b) {
    return Point(a.x+b.x, a.y+b.y);
  }
  friend Point operator - (const Point &a, const Point &b) {
    return Point(a.x-b.x, a.y-b.y);
  }
} hpi[MAXN], q[MAXN];
class Line {
  public :Point a, b;
  Line () { }
  Line (const Point &a, const Point &b) : a(a), b(b) { }
} ;
char announce[10];
int cnt_hpi;
double A, B, C;
double xmulti(const Point &a, const Point &b)
{
  return a.x*b.y - a.y*b.x;
}
Line MidPP(const Line &l)     //求中垂线
//本题只用到一般式(A,B,C)，所以其实后面部分可以去掉
{
  Line res;
  res.a = Point( (l.a.x + l.b.x)/2, (l.a.y + l.b.y)/2 );
  //一般式
  A = l.b.x - l.a.x;
  B = l.b.y - l.a.y;
  C = (l.a.y-l.b.y)*res.a.y + (l.a.x-l.b.x)*res.a.x;
  //两点式
  if(dblcmp(A) != 0) {
    res.b = Point(-C/A, 0);
    if(res.b == res.a)
      res.b = Point(-(C-B*1e10)/A, 1e10);
  } else {
    res.b = Point(0, -C/B);
    if(res.b == res.a)
      res.b = Point(1e10, -(C-A*1e10)/B);
  }
  return res;
}
Point intersection(const Point &a, const Point &b, const Point &c, const Point &d)
{
  //lrj书上是inter(P, u, Q, v)，其中P，u分别是第一条直线的一个点和方向向量，这里我用b-a就得到u了
  Point u = b-a, v = d - c;   //u,v是两条直线的方向向量
  Point tmp = a - c;
  double t = xmulti(v, tmp)/xmulti(u, v);
  return a + u*t;
}
Point intersection(const Point &a, const Point &b, double A, double B, double C)
{
  //两种方法求交点，前者是先把Ax+By+C=0转成两个点的形式，后者直接解方程，我觉得前者比较具有通用性
  //虽说由于前者的前提是要两条直线有唯一交点，所以前期要写些判断操作(下面这4个if)。
  Point p1, p2;
  if(dblcmp(A) == 0)      p1 = Point(1, -C/B), p2 = Point(2, -C/B);
  else if(dblcmp(B) == 0) p1 = Point(-C/A, 1), p2 = Point(-C/A, 2);
  else p1 = Point(1, (-C-A*1)/B), p2 = Point(2, (-C-A*2)/B);

  if(!dblcmp(xmulti(p1-p2, a-b))) return a;
  return intersection(p1, p2, a, b);

  //解方程求交点
  //double u = fabs(A * a.x + B * a.y + C);
  //double v = fabs(A * b.x + B * b.y + C);
  //return Point( (v*a.x + u*b.x)/(u+v),
  //              (v*a.y + u*b.y)/(u+v) );
}
void init_HPI()
{
  cnt_hpi = 4;
  hpi[1] = hpi[5] = Point(0, 0);
  hpi[2] = Point(0, 10);
  hpi[3] = Point(10,10);
  hpi[4] = hpi[0] = Point(10,0);
}
bool cmp(double x)
{
  if(announce[0] == 'S') return !dblcmp(x);   //same
  else if(announce[0] == 'H') return dblcmp(x) == 1; //closer
  else return dblcmp(x) == -1;    //farther
}
void cut()
{
  int m = 0;
  for(int i = 1; i <= cnt_hpi; i++) {
    if(cmp(A*hpi[i].x + B*hpi[i].y + C))
      q[++m] = hpi[i];
    else {
      if(cmp(A*hpi[i-1].x + B*hpi[i-1].y + C))
        q[++m] = intersection(hpi[i], hpi[i-1], A, B, C);
      if(cmp(A*hpi[i+1].x + B*hpi[i+1].y + C))
        q[++m] = intersection(hpi[i], hpi[i+1], A, B, C);
    }
  }
  cnt_hpi = m;
  for(int i = 1; i <= m; i++) hpi[i] = q[i];
  hpi[0] = hpi[m], hpi[m+1] = hpi[1];
}
double Area(const Point *p, int n);
int main()
{
  freopen("in.txt","r",stdin);
  Point u[2] = { Point(0,0) };
  int cur = 1;
  double ans = 10 * 10;
  init_HPI();
  while(scanf("%lf%lf%s", &u[cur].x, &u[cur].y, announce) != EOF) {
    Line midpp = MidPP(Line(u[1-cur], u[cur]));
  //  printf("(%.2f %.2f)---(%.2f %.2f)\n", midpp.a.x,midpp.a.y,midpp.b.x,midpp.b.y);
    cut();
    printf("%.2f\n", fabs(Area(hpi, cnt_hpi)));
    cur = 1 - cur;
  }
  return 0;
}

double Area(const Point *p, int n)
{
  double area = 0;
  for(int i = 1; i <= n; i++) area += xmulti(p[i], p[i+1]);
  area = area > 0 ? area : -area;
  return area/2;
}

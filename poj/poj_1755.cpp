/*
  计算几何 半平面交判定线性不等式是否有解 半平面交解不等式

  题目：铁人三项，每个人在某一项中有确定的速度，裁判可以决定某一项比赛的路程为多少，问对于某个人，
        是否存在一种安排能使他拿到第一，而且不能是并列。

  思路：设比赛总长度为1(我是用1000，减少精度误差)，其中游泳长度为x，自行车产度为y，赛跑长度为1-x-y
        则i能打败j需要：x/vi + y/ui + z/wi < x/vj + y/uj + z/wj，
        化简一下，再两边同时处于z，就得到
        A = 1/vi - 1/vj
        B = 1/ui - 1/uj
        C = 1/wi - 1/wj

        这样，问题就转化成了问一系列不等式是否有解（怎么这么像差分约束？）

        对于每个选手i，可以得到n-1个半平面，加上x>0,y>0,1-x-y>0
        然后就用半平面交来判断这n-1+3个线性不等式是否有解。

        因为解域可能是无界的，所以我们可以用一个很大的矩形代表整个平面。

        为了减少精度误差，我对A,B,C都乘上了1000，还有，1/ui - 1/uj化为(ui+uj)/(ui*uj)也能减少精度误差
*/
#include <stdio.h>
#include <math.h>
#define MAXN 1005
#define EPS  1e-11
#define INF  10000
#define unit (1000)
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
  friend Point operator * (const Point &a, const double k) {
    return Point(a.x*k, a.y*k);
  }
  friend Point operator - (const Point &a, const Point &b) {
    return Point(a.x-b.x, a.y-b.y);
  }
  friend Point operator + (const Point &a, const Point &b) {
    return Point(a.x+b.x, a.y+b.y);
  }
} hpi[MAXN], q[MAXN];
double U[MAXN], V[MAXN], W[MAXN], A, B, C;
int n, cnt_hpi;

double xmulti(const Point &a, const Point &b)
{
  return a.x*b.y - a.y*b.x;
}
int dblcmp(double x)
{
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
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
  hpi[5] = hpi[1] = Point(EPS, EPS);
  hpi[2] = Point(EPS, INF);
  hpi[3] = Point(INF, INF);
  hpi[0] = hpi[4] = Point(INF, EPS);
  cnt_hpi = 4;
}
void cut()
{
  int m = 0;
  for(int i = 1; i <= cnt_hpi; i++) {
    if(A*hpi[i].x + B*hpi[i].y + C > 0)       //不能等于怎么办
      q[++m] = hpi[i];
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
bool HPI(int o_o)
{
  init_HPI();
  for(int i = 1; i <= n; i++) if(i != o_o) {
    //为什么我按照lrj的A/B/C不对呢？
    //A = (unit*(W[o_o]-V[o_o])/(V[o_o]*W[o_o])) - (unit*(W[i]-V[i])/(V[i]*W[i]));
    //B = (unit*(W[o_o]-U[o_o])/(U[o_o]*W[o_o])) - (unit*(W[i]-U[i])/(U[i]*W[i]));
    //C = unit*(W[i]-W[o_o])/(W[o_o]*W[i]);

    A = (U[o_o]-U[i])/(U[o_o]*U[i]);
    B = (V[o_o]-V[i])/(V[o_o]*V[i]);
    C = (W[o_o]-W[i])/(W[o_o]*W[i]);
    cut();
  }
  return cnt_hpi > 0;
}
int main()
{
  while(scanf("%d", &n) != EOF) {
    for(int i = 1; i <= n; i++) scanf("%lf%lf%lf", &V[i], &U[i], &W[i]);

    for(int i = 1; i <= n; i++) puts(HPI(i) ? "Yes" : "No");
  }
  return 0;
}

#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAXN 20000*3
#define EPS  1e-10

class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
  double operator ^ (const Point &b) const {
//    printf("%f %f %f %f\n", x, y, b.x, b.y);
    return x*b.y - y*b.x;
  }
  Point  operator - (const Point &b) const {
    return Point(x-b.x, y-b.y);
  }
} hpi[MAXN];
class Line {
  public : Point s, e;
  double A, B, C, k;
  Line () {}
  Line (double x1, double y1, double x2, double y2) : s(x1, y2), e(x2, y2) {
    A = y2 - y1, B = x1 - x2, C = x2*y1 - x1*y2;
    k = atan2(y2-y1, x2-x1);
  }
  Point  operator & (const Line &b) const {     //直线交点
    double t = ((s - b.s)^(b.s - b.e)) / ((s - e)^(b.s - b.e));
    return Point(s.x+(e.x-s.x)*t, s.y+(e.y-s.y)*t);
  }
} line[MAXN], Q[MAXN];
int n, cnt_hpi;

int dblcmp(double x)
{
  if(fabs(x) <= EPS) return 0;
  return x > 0 ? 1 : -1;
}
bool is_out(const Point &a, const Line &l)
{
//  return l.A*a.x + l.B*a.y + l.C < 0;     //根据题目调整方向   这个不可以吗？
  return dblcmp((a-l.s) ^ (l.e-l.s)) > 0;   //网上的
}
bool cmp_HPI(const Line &a, const Line &b) {
  if(!dblcmp(a.k - b.k)) return dblcmp((b.e-b.s)^(a.e-b.e)) >= 0;   //方向
  return a.k < b.k;
}
void init_HPI()
{
  line[0] = Line(0, 0, 10000, 0);
  line[1] = Line(10000, 0, 10000, 10000);
  line[2] = Line(10000,10000, 0, 10000);
  line[3] = Line(0, 10000, 0, 0);
}
bool HPI(Line line[], int n, Point hpi[], int &cnt_hpi)
{
  sort(line, line+n, cmp_HPI);
  int tot = 1;
  for(int i = 1; i < n; i++) if(dblcmp(line[i].k-line[i-1].k)) line[tot++] = line[i];
  n = tot;

  int head = 1, tail = 0;
  Q[0] = line[0], Q[1] = line[1];
  for(int i = 2; i < n; i++) {
//    if(dblcmp( (Q[tail].e-Q[tail].s) ^ (Q[tail+1].e-Q[tail+1].s) ) == 0
//       || dblcmp( (Q[head].e-Q[head].s) ^ (Q[head-1].e-Q[head-1].s) ) == 0)
//        return false;        //不理解

    while(head > tail && is_out(Q[head] & Q[head-1], line[i])) head--;
    while(head > tail && is_out(Q[tail] & Q[tail+1], line[i])) tail++;

    Q[++head] = line[i];
  }

  while(head > tail && is_out(Q[head] & Q[head-1], Q[tail])) head--;
  while(head > tail && is_out(Q[tail] & Q[tail+1], Q[head])) tail++;

  cnt_hpi = 0;
  for(int i = tail; i < head; i++) hpi[cnt_hpi++] = Q[i] & Q[i+1];
  if(tail < head - 1) hpi[cnt_hpi++] = Q[head] & Q[tail];
  return cnt_hpi > 2;
}
double Area(const Point p[], int n);
int main()
{
  freopen("in.txt","r",stdin);
  double x1, x2, y1, y2;
  while(scanf("%d", &n) != EOF) {
    init_HPI();
    n += 4;
    for(int i = 4; i < n; i++) {
      scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
      line[i] = Line(x1,y1,x2,y2);
    }
    if(!HPI(line, n, hpi, cnt_hpi)) { puts("hello world 0.0"); continue; }
    double area = Area(hpi, cnt_hpi);
    printf("%.1f\n", area);
  }
  return 0;
}
double Area(const Point p[], int n)
{
  double area = 0.0;
  for(int i = 0; i < n; i++) area += (p[i] ^ p[(i+1)%n]);
  return fabs(area)/2;
}

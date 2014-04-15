/*
  ���㼸�� ��ƽ�潻 �����ƽ�
  ����: �ڶ�����ڰ��������뾶ΪR��Բ������Բ��Χ���ܳ�������Σ��������ཻ��������
        �У�ʹ������Բ���ǵ����򾡿��ܴ��غϵĲ���ֻ��һ�Σ���������Բ��Բ�����ꡣ

  ˼·���������ƽ�R��Ȼ�����ƽ�潻����Ŀ��֤���ڣ���Ȼ���ڰ�ƽ�潻���ҵ���������
        ��Զ�ĵ㣬������������Բ�����š�
        ȡԲ�������ƺ�Ķ���εİ�ƽ�潻���ܹ���֤Բ����������Ρ���ȡ��ƽ�潻�ϵ�����
        ��Զ�ĵ㣬������Բ��Բ�ľ����ʹ������Բ�غϵĲ��־���С����Ϊʲô������Զ
        �ĵ���ڰ�ƽ�潻�Ķ����ϣ���Ϊ��ƽ�潻�Ǹ�͹����Σ���͹�������������Զ�ĵ�
        һ���ڶ����ϡ�
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

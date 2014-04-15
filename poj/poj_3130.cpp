/*
  ���㼸�� ��ƽ�潻
  ���⣺�ж��Ƿ���ڰ�ƽ�潻�����Ѿ���˳ʱ�������

  ˼·��hpi���ƽ�潻�㼯��cnt_HPI��¼����
        A, B, C�����Է���A*x + B*y + C = 0�Ĳ���

        ��������lrj˵��Ϊ��Ӧ���������䣬��ȷ��4����˵��ģ��ģ�û�ҵ����ʵģ���������

        �������Ϊ��ƽ�潻���ܺ�С������Ϊһ���㣬���Բ������ж��������ƽ�潻


        ֮ǰ��Ҫ��������������Ļ�(���������)����p[i],p[(i+1)%n](�±��0��ʼ������������һ�ַ�����
        �±��1��ʼ��p[0] = p[n]��p[n+1] = p[1]��Ȼ��Ͳ���ÿ�ζ�ģ�ˣ��÷���
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

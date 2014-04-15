/*
  ���㼸�� ��ƽ�潻�ж����Բ���ʽ�Ƿ��н� ��ƽ�潻�ⲻ��ʽ

  ��Ŀ���������ÿ������ĳһ������ȷ�����ٶȣ����п��Ծ���ĳһ�������·��Ϊ���٣��ʶ���ĳ���ˣ�
        �Ƿ����һ�ְ�����ʹ���õ���һ�����Ҳ����ǲ��С�

  ˼·��������ܳ���Ϊ1(������1000�����پ������)��������Ӿ����Ϊx�����г�����Ϊy�����ܳ���Ϊ1-x-y
        ��i�ܴ��j��Ҫ��x/vi + y/ui + z/wi < x/vj + y/uj + z/wj��
        ����һ�£�������ͬʱ����z���͵õ�
        A = 1/vi - 1/vj
        B = 1/ui - 1/uj
        C = 1/wi - 1/wj

        �����������ת��������һϵ�в���ʽ�Ƿ��н⣨��ô��ô����Լ������

        ����ÿ��ѡ��i�����Եõ�n-1����ƽ�棬����x>0,y>0,1-x-y>0
        Ȼ����ð�ƽ�潻���ж���n-1+3�����Բ���ʽ�Ƿ��н⡣

        ��Ϊ����������޽�ģ��������ǿ�����һ���ܴ�ľ��δ�������ƽ�档

        Ϊ�˼��پ������Ҷ�A,B,C��������1000�����У�1/ui - 1/uj��Ϊ(ui+uj)/(ui*uj)Ҳ�ܼ��پ������
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
  //lrj������inter(P, u, Q, v)������P��u�ֱ��ǵ�һ��ֱ�ߵ�һ����ͷ�����������������b-a�͵õ�u��
  Point u = b-a, v = d - c;   //u,v������ֱ�ߵķ�������
  Point tmp = a - c;
  double t = xmulti(v, tmp)/xmulti(u, v);
  return a + u*t;
}
Point intersection(const Point &a, const Point &b, double A, double B, double C)
{
  //���ַ����󽻵㣬ǰ�����Ȱ�Ax+By+C=0ת�����������ʽ������ֱ�ӽⷽ�̣��Ҿ���ǰ�߱ȽϾ���ͨ����
  //��˵����ǰ�ߵ�ǰ����Ҫ����ֱ����Ψһ���㣬����ǰ��ҪдЩ�жϲ���(������4��if)��
  Point p1, p2;
  if(dblcmp(A) == 0)      p1 = Point(1, -C/B), p2 = Point(2, -C/B);
  else if(dblcmp(B) == 0) p1 = Point(-C/A, 1), p2 = Point(-C/A, 2);
  else p1 = Point(1, (-C-A*1)/B), p2 = Point(2, (-C-A*2)/B);

  if(!dblcmp(xmulti(p1-p2, a-b))) return a;
  return intersection(p1, p2, a, b);

  //�ⷽ���󽻵�
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
    if(A*hpi[i].x + B*hpi[i].y + C > 0)       //���ܵ�����ô��
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
    //Ϊʲô�Ұ���lrj��A/B/C�����أ�
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

/*
  ��������  �����δ��� �㵽ֱ�ߵ�ͶӰ

  ˼·����lrj�����ҵ��˵㵽ֱ�ߵ�ͶӰ�İ壬�ù�����������ζ���Ĵ�
        �㣬�����������ߵĽ�����Ǵ�����

        ���Ƕ�˵�����㼸����Ŀ�Է���һ�������Ҫ��EPS��Ӧ����Ϊ�˷�
        ֹ-0.00֮������鷢��

  ժ�����ĵ����ʣ�
  http://baike.baidu.com/link?url=-w0YFewGmwqvIkSoSCmhIPy4M3RLcUDA5F5FHQCvE4uJ1sP7k7B5i7_TIcQHHLix0e4VR_F0hXl98-0wBdI9Yq
  ���ģ������ε������߻����ӳ����ཻ��һ�㣬����Ϊ�����εĴ��ġ�

  ��SABC��������ΪAD��BE��CF������D��E��FΪ���㣬����ΪH����A��B��C�ĶԱ߷ֱ�Ϊa��b��c
1����������εĴ������������ڣ�ֱ�������εĴ�����ֱ�Ƕ����ϣ��۽������εĴ�������������.
2�������εĴ����������������ε����ģ�����˵�������ε������������������εĴ��ģ�
3�� ����H�������ߵĶԳƵ㣬���ڡ�ABC�����Բ�ϡ�
4�� ��ABC�У��������ĵ㹲Բ��������(ÿ���ĸ�)���Ƶ�ֱ�������Σ���AH��HD=BH��HE=CH��HF��
5�� H��A��B��C�ĵ�����һ������������Ϊ����������εĴ���(�����������ĵ�Ϊһ��������)��
6�� ��ABC����ABH����BCH����ACH�����Բ�ǵ�Բ��
7�� �ڷ�ֱ���������У���H��ֱ�߽�AB��AC����ֱ�߷ֱ���P��Q���� AB/AP��tanB+
�����εĴ��������ĵ�λ�ù�ϵ
�����εĴ��������ĵ�λ�ù�ϵ
AC/AQ��tanC=tanA+tanB+tanC��
8�� ��������һ���㵽���ĵľ��룬�������ĵ��Աߵľ����2����
9�� ��O��H�ֱ�Ϊ��ABC�����ĺʹ��ģ����BAO=��HAC����ABH=��OBC����BCO=��HCA��
10�� ��������εĴ��ĵ�������ľ���֮�͵���������Բ�����Բ�뾶֮�͵�2����
11�� ��������εĴ����Ǵ��������ε����ģ���������ε��ڽ�������(������ԭ�����εı���)�У��Դ��������ε��ܳ���̡�
12����ķ��(Simson)������ķ���ߣ�
    ��һ���������ε������������ߵĴ��㹲�ߵĳ�Ҫ�����Ǹõ����������ε����Բ�ϡ�
13�� ����ǨSABC����һ��P����ôP�Ǵ��ĵĳ�ֱ�Ҫ������PB*PC*BC+PB*PA*AB+PA*PC*AC=AB*BC*CA��
*/
#include <stdio.h>
#define EPS 1e-9
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
  Point operator - (const Point &b) const {
    return Point(x-b.x, y-b.y);
  }
  Point operator + (const Point &b) const {
    return Point(x+b.x, y+b.y);
  }
  double operator *(const Point &b) {
    return x*b.x + y*b.y;
  }
  Point operator *(double k) {
    return Point(x*k, y*k);
  }
  double operator ^(const Point &b) {
    return x*b.y - y*b.x;
  }
} ;
class Line {
  public : Point s, e;
  Line () {}
  Line (const Point &s, const Point &e) : s(s), e(e) {}
  Point operator & (const Line &b) const {  //�󽻵�
    double t = ((s - b.s)^(b.s - b.e)) / ((s - e)^(b.s - b.e));
    return Point(s.x+(e.x-s.x)*t, s.y+(e.y-s.y)*t);
  }
};
Point GetLineProjection(const Point P, const Point A, const Point B)
{ //P����ֱ��AB��ͶӰ��
  Point v = B - A;
  return A + v*( (v*(P-A))/(v*v) );
}
Point Get_Ortho(const Point &A, const Point &B, const Point &C)
{ //������ABC�Ĵ���
  Point D = GetLineProjection(A, B, C);
  Point E = GetLineProjection(B, A, C);
  return Line(A, D) & Line(B, E);
}
int main()
{
  freopen("in.txt","r",stdin);
  int cases;
  Point A, B, C;
  scanf("%d", &cases);
  while(cases--) {
    scanf("%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
    Point Ortho = Get_Ortho(A, B, C);
    printf("%.4f %.4f\n", Ortho.x+EPS, Ortho.y+EPS);
  }
  return 0;
}

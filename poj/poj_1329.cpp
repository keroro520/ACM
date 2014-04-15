/*
  ��������  ���������Բ
���⣺��������Բ�ϵĵ㣬��Բ�����ֱ��ʽ�������ռ�֪ʶ��


http://www.th7.cn/Program/cp/201210/100817.shtml
http://blog.himdd.com/archives/415

���Բ�뾶:��ʽ:a/sinA=b/sinB=c/sinC=2R (R�������Բ�뾶)
��������������٣����������Ҷ���a^2=b^2+c^2��2bc��cosA
�����cosA=(b^2+c^2��a^2)/2bc �����ù�ʽ��sinA^2+cosA^2=1
ȷ�� sinA=����(1��cosA^2) =����[(a^2+b^2+c^2)^2-2(a^4+b^4+c^4)]/(2bc)
Ȼ����� a/sinA=2R���R�� R=abc/����[(a^2+b^2+c^2)^2-2(a^4+b^4+c^4)]

���壺��ƽ���ϵ�����A(x1,y1),B(x2,y2),C(x3,y3),����
S(A,B,C) = (x1-x3)*(y2-y3) - (y1-y3)*(x2-x3)

��֪�����ε���������ΪA(x1,y1),B(x2,y2),C(x3,y3)����������ε�����Ϊ��
           S((x1*x1+y1*y1, y1), (x2*x2+y2*y2, y2), (x3*x3+y3*y3, y3))
x0 = -----------------------------------------------------------
                       2*S(A,B,C)

         S((x1,x1*x1+y1*y1), (x2, x2*x2+y2*y2), (x3, x3*x3+y3*y3))
y0 = -----------------------------------------------------------
            2*S(A,B,C)
*/
/*
����һ����⣺
��֪Բ��3�㣬Բ����
�����3�߳�,�ɺ��׹�ʽ�ó����
S=sqrt(p*(p-a)*(p-b)*(p-c)) p=(a+b+c)/2;
�������������ʽS=1/2*a*b*sin(C)
�����Ҷ���a/sin(A)=b/sin(B)=c/sin(C)=ֱ��
�ɵ�ֱ��=a*b*c/2/S; (a,b,cΪ���߳�)

��Բ�����ꡣ���ã�G�ǨSABC���ĵĳ�Ҫ������
(����GA+����GB)������AB= (����GB+����GC)������BC
=(����GC+����GA)������CA=����0.
������ʵ�֤�������׵ģ�ֻ��Ҫ�����д��ߣ�
�Ϳ���֤����������ˡ������������Ա�����б�ʣ��Լ�����б�ʲ����ڵȺܶ����
*/

#include <stdio.h>
#include <math.h>
class Point {
  public : double x, y;
  Point () {}
  Point (double x, double y) : x(x), y(y) {}
} ;
double _dis(const Point &a, const Point &b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
double xmulti(const Point &a, const Point &b, const Point &c)
{
  return (a.x-c.x)*(b.y-c.y) - (a.y-c.y)*(b.x-c.x);
}

Point get_O(const Point &a, const Point &b, const Point &c)  //���������ԲԲ��
{
  /*��������main�����ģ�Ų�������
    double a = _dis(C, B), b = _dis(A, C), c = _dis(A, B);
    double p = (a+b+c) * 0.5;
    double S = sqrt( p*(p-a)*(p-b)*(p-c) );
    double R = a*b*c/(2*2*S);             ���Բ�뾶
  */
  double x0 = xmulti(Point(a.x*a.x+a.y*a.y, a.y),
                     Point(b.x*b.x+b.y*b.y, b.y),
                     Point(c.x*c.x+c.y*c.y, c.y));
  double y0 = xmulti(Point(a.x, a.x*a.x+a.y*a.y),
                     Point(b.x, b.x*b.x+b.y*b.y),
                     Point(c.x, c.x*c.x+c.y*c.y));
  x0 /= 2*xmulti(a, b, c);
  y0 /= 2*xmulti(a, b, c);
  return Point(x0, y0);
}
int main()
{
  freopen("in.txt","w",stdout);
  Point A, B, C;
  while(scanf("%lf%lf%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y) != EOF) {

    Point O = get_O(A, B, C);
    double t = O.x*O.x+O.y*O.y-R*R;
    printf("(x %c %.3f)^2 + (y %c %.3f)^2 = %.3f^2\n",
           O.x>0?'-':'+',(O.x>0?1:-1)*O.x,O.y>0?'-':'+',(O.y>=0?1:-1)*O.y,R);
    printf("x^2 + y^2 %c %.3fx %c %.3fy %c %.3f = 0\n",
           2*O.x>0?'-':'+',(O.x>0?1:-1)*2*O.x,2*O.y>0?'-':'+',(O.y>=0?1:-1)*2*O.y,t>=0?'+':'-',(t>=0?1:-1)*t);
    puts("");
  }
  return 0;
}

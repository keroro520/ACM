/*
  解析几何  三角形外接圆
题意：给你三个圆上的点，求圆的两种表达式。首先普及知识：


http://www.th7.cn/Program/cp/201210/100817.shtml
http://blog.himdd.com/archives/415

外接圆半径:公式:a/sinA=b/sinB=c/sinC=2R (R就是外接圆半径)
本题可以这样：①．先利用余弦定理：a^2=b^2+c^2－2bc·cosA
求出：cosA=(b^2+c^2－a^2)/2bc 在利用公式：sinA^2+cosA^2=1
确定 sinA=根号(1－cosA^2) =根号[(a^2+b^2+c^2)^2-2(a^4+b^4+c^4)]/(2bc)
然后代入 a/sinA=2R求出R． R=abc/根号[(a^2+b^2+c^2)^2-2(a^4+b^4+c^4)]

定义：设平面上的三点A(x1,y1),B(x2,y2),C(x3,y3),定义
S(A,B,C) = (x1-x3)*(y2-y3) - (y1-y3)*(x2-x3)

已知三角形的三个顶点为A(x1,y1),B(x2,y2),C(x3,y3)，则该三角形的外心为：
           S((x1*x1+y1*y1, y1), (x2*x2+y2*y2, y2), (x3*x3+y3*y3, y3))
x0 = -----------------------------------------------------------
                       2*S(A,B,C)

         S((x1,x1*x1+y1*y1), (x2, x2*x2+y2*y2), (x3, x3*x3+y3*y3))
y0 = -----------------------------------------------------------
            2*S(A,B,C)
*/
/*
另外一个题解：
已知圆的3点，圆方程
先求出3边长,由海伦公式得出面积
S=sqrt(p*(p-a)*(p-b)*(p-c)) p=(a+b+c)/2;
由三角形面积公式S=1/2*a*b*sin(C)
和正弦定理a/sin(A)=b/sin(B)=c/sin(C)=直径
可得直径=a*b*c/2/S; (a,b,c为三边长)

求圆心坐标。利用：G是⊿ABC外心的充要条件是
(向量GA+向量GB)·向量AB= (向量GB+向量GC)·向量BC
=(向量GC+向量GA)·向量CA=向量0.
这个性质的证明很容易的，只需要利用中垂线，
就可以证明这个性质了。利用向量可以避免求斜率，以及考虑斜率不存在等很多情况
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

Point get_O(const Point &a, const Point &b, const Point &c)  //三角型外接圆圆心
{
  /*本来放在main函数的，挪过来这边
    double a = _dis(C, B), b = _dis(A, C), c = _dis(A, B);
    double p = (a+b+c) * 0.5;
    double S = sqrt( p*(p-a)*(p-b)*(p-c) );
    double R = a*b*c/(2*2*S);             外接圆半径
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

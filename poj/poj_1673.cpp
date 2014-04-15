/*
  解析几何  三角形垂心 点到直线的投影

  思路：在lrj书上找到了点到直线的投影的板，拿过来算出三角形顶点的垂
        足，再算两条垂线的交点就是垂心了

        人们都说，计算几何题目以防万一，输出都要加EPS，应该是为了防
        止-0.00之类的事情发生

  摘抄垂心的性质：
  http://baike.baidu.com/link?url=-w0YFewGmwqvIkSoSCmhIPy4M3RLcUDA5F5FHQCvE4uJ1sP7k7B5i7_TIcQHHLix0e4VR_F0hXl98-0wBdI9Yq
  垂心：三角形的三条高或其延长线相交于一点，这点称为三角形的垂心。

  设⊿ABC的三条高为AD、BE、CF，其中D、E、F为垂足，垂心为H，角A、B、C的对边分别为a、b、c
1、锐角三角形的垂心在三角形内；直角三角形的垂心在直角顶点上；钝角三角形的垂心在三角形外.
2、三角形的垂心是它垂足三角形的内心；或者说，三角形的内心是它旁心三角形的垂心；
3、 垂心H关于三边的对称点，均在△ABC的外接圆上。
4、 △ABC中，有六组四点共圆，有三组(每组四个)相似的直角三角形，且AH·HD=BH·HE=CH·HF。
5、 H、A、B、C四点中任一点是其余三点为顶点的三角形的垂心(并称这样的四点为一—垂心组)。
6、 △ABC，△ABH，△BCH，△ACH的外接圆是等圆。
7、 在非直角三角形中，过H的直线交AB、AC所在直线分别于P、Q，则 AB/AP·tanB+
三角形的垂心与外心的位置关系
三角形的垂心与外心的位置关系
AC/AQ·tanC=tanA+tanB+tanC。
8、 三角形任一顶点到垂心的距离，等于外心到对边的距离的2倍。
9、 设O，H分别为△ABC的外心和垂心，则∠BAO=∠HAC，∠ABH=∠OBC，∠BCO=∠HCA。
10、 锐角三角形的垂心到三顶点的距离之和等于其内切圆与外接圆半径之和的2倍。
11、 锐角三角形的垂心是垂足三角形的内心；锐角三角形的内接三角形(顶点在原三角形的边上)中，以垂足三角形的周长最短。
12、西姆松(Simson)定理（西姆松线）
    从一点向三角形的三边所引垂线的垂足共线的充要条件是该点落在三角形的外接圆上。
13、 设锐角⊿ABC内有一点P，那么P是垂心的充分必要条件是PB*PC*BC+PB*PA*AB+PA*PC*AC=AB*BC*CA。
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
  Point operator & (const Line &b) const {  //求交点
    double t = ((s - b.s)^(b.s - b.e)) / ((s - e)^(b.s - b.e));
    return Point(s.x+(e.x-s.x)*t, s.y+(e.y-s.y)*t);
  }
};
Point GetLineProjection(const Point P, const Point A, const Point B)
{ //P点在直线AB的投影点
  Point v = B - A;
  return A + v*( (v*(P-A))/(v*v) );
}
Point Get_Ortho(const Point &A, const Point &B, const Point &C)
{ //三角形ABC的垂心
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

/*
  计算几何  pick定理 blabla
http://blog.sina.com.cn/s/blog_6635898a0100mjn1.html
http://blog.csdn.net/tsaid/article/details/7096631

题意：在一个平面直角坐标系内，有一个以整点为顶点的多边形，问1.这个多边形的边所覆盖的整点有多少个。2.这个多边形内部的整点有多少个。3.这个多边形的面积。

思路：基础的多边形面积，加上pick定理。先求出多边形面积和边上的点数，再用pick定理求内部的点数。

pick定理：在一个平面直角坐标系内，以整点为顶点的简单多边形（任两边不交叉），它内部整点数为a，它的边上（包括顶点）的整点数为b，则它的面积S = a+b/2-1。
          S = a+b/2-1
求边上的点数也有一个很重要的结论：以整点为顶点的线段，覆盖的整点数为GCD(dx,dy)，其中，dxdy分别为线段横向占的点数和纵向占的点数。如果dx或dy为0，则覆盖的点数为dy或dx。

*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define MAXN 200
typedef long long ll;
class Point {
  public : int x,y ;
} p[MAXN];
int n;
ll xmulti(const Point &a, const Point &b)
{
  return (int)((ll)a.x*(ll)b.y - (ll)a.y*(ll)b.x);
}
double Area()
{
  double area = 0^0;
  for(int i = 0; i < n; i++) area += xmulti(p[i], p[i+1]);
  return area/2;
}
int GCD(int a, int b)
{
  return b == 0 ? a : GCD(b, a%b);
}
int calc_point(const Point &a, const Point &b)
{
  int dx = abs(a.x-b.x), dy = abs(a.y-b.y);
  return GCD(max(dx, dy), min(dx, dy));
}
int main()
{
  //freopen("in.txt","r",stdin);
  int cases, Cas = 0, dx, dy;
  scanf("%d", &cases);
  while(cases--) {
    scanf("%d", &n);
    p[0].x = p[0].y = 0;
    int point_on = 0;
    for(int i = 1; i <= n; i++) {
      scanf("%d%d", &dx, &dy);
      point_on += GCD(max(abs(dx), abs(dy)), min(abs(dx), abs(dy)));
      p[i].x = p[i-1].x + dx, p[i].y = p[i-1].y + dy;
    }
    double area = Area( );
    area = area > 0 ? area : -area;
    int point_in = (int)area - point_on/2 + 1;
    printf("Scenario #%d:\n", ++Cas );
    printf("%d %d %.1f\n", point_in, point_on, area);
    puts("");
  }
  return 0;
}

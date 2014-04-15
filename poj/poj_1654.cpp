/*
  求多边形面积 area += xmulti(p[j], p[j+1]);


  long long不要用abs，懒得man了，猜测是abs返回值为int
*/
#include <algorithm>
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAXN 1000010
typedef __int64 ll;
class Point {
  public : int x, y;
  Point () { }
  Point (int x, int y) : x(x), y(y) { }
} p[MAXN];
char str[MAXN];
ll xmulti(const Point &a, const Point &b)
{
  return (ll)a.x*(ll)b.y - (ll)a.y*(ll)b.x;
}
void New_Point(char ch, const Point &pre, Point &now)
{
  switch (ch) {
    case '1' : now = Point(pre.x-1, pre.y-1); break;
    case '2' : now = Point(pre.x,   pre.y-1); break;
    case '3' : now = Point(pre.x+1, pre.y-1); break;
    case '4' : now = Point(pre.x-1, pre.y  ); break;
    case '6' : now = Point(pre.x+1, pre.y  ); break;
    case '7' : now = Point(pre.x-1, pre.y+1); break;
    case '8' : now = Point(pre.x,   pre.y+1); break;
    case '9' : now = Point(pre.x+1, pre.y+1); break;
  }
}
int main()
{
 // freopen("in.txt", "r", stdin);
  int cases;
  scanf("%d", &cases);
  while(cases--) {
    scanf("%s", str);
    int i = 0;
    p[i++] = Point(0, 0);
    while(str[i-1] != '5') {
      New_Point(str[i-1], p[i-1], p[i]);
      i++;
    }
    p[i++] = Point(0, 0); //TODO
    ll area = 0;
    for(int j = 0; j < i; j++) area += xmulti(p[j], p[j+1]);
    area = area > 0 ? area : -area;

    if(area % 2 == 1) cout << area/2 << ".5" << endl; else cout << area/2 << endl;;
  }
  return 0;
}

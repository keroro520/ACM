/*
  计算几何 pick 定理

  注意别写成if( Sum(a[i].x+a[i].y) == 0) break; 因为遇到-1 1 -1 1 -1 1这类的数据就跪了...
*/
#include <math.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
int a[5][5];
const int n = 3;
int GCD(int a, int b) { return b == 0 ? a : GCD(b, a%b); }
int calc(int i, int j)
{
  int dx = abs(a[i][0] - a[j][0]), dy = abs(a[i][1] - a[j][1]);
  return GCD(max(dx, dy), min(dx, dy));
}
int xmulti(int x1, int y1, int x2, int y2)
{
  return x1*y2 - x2*y1;
}
double Area()
{
  return fabs( 1.0*xmulti(a[2][0] - a[0][0], a[2][1] - a[0][1],   a[1][0] - a[0][0], a[1][1] - a[0][1]) ) / 2;
}
int main()
{
  while(true) {
    bool flag = false;
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &a[i][0], &a[i][1]);
      if(a[i][0] || a[i][1]) flag = true;
    }
    if(!flag) break;
    int on = 0;
    for(int i = 0; i < n; i++) {
      on += calc(i, (i+1)%n);
    }
    double area = Area();
    int in = (int)area - on/2 + 1;
    printf("%d\n", in);

  }
      return 0;
}

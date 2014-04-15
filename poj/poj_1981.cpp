/*
  计算几何 弧 弧的覆盖 单位圆最多能覆盖平面上多少个点
  题意：求单位圆最多能覆盖平面上多少个点
  思路：先枚举一个点，再枚举所有与它距离小于2的点，这样就可以求出相交弧，把所有弧保存下来，并离
    散化，保存方向以及极角，排序，就能算出覆盖次数最多的一段弧，这个次数也就是答案了
    Ps：求交点时可以用一种巧妙的方法，那就是求出2个圆心的斜率并用arctan求出相差的角度（邻边
    是圆心距/2，斜边是R）
    建立极角的时候，不是以枚举的圆心 i->j 方向的向量，而是 j->i 方向的向量，因为 i->j 方向
    不能完全判断圆的方向，在极角排序的时候会出错


  上面都是摘抄的>O<，因为不太理解啊~~~
*/
#include <math.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define MAXN 305
class Point {
  public : double x, y;
} p[MAXN];
class Label {
  public : double ang; bool in;
  Label(double ang, bool in) : ang(ang), in(in) {}
  bool operator < (const Label &b) const {
    return ang < b.ang;
  }
};
double _dis(const Point &a, const Point &b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
vector<Label> v;
int n;
int main()
{
  freopen("in.txt","r",stdin);
  while(scanf("%d", &n), n) {
    for(int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);

    int ans = 1;
    for(int i = 0; i < n; i++) {
      v.clear();
      for(int j = 0; j < n; j++) if(i != j) {
        if(_dis(p[i], p[j]) > 2) continue;
        double ang1 = atan2(p[i].y-p[j].y, p[i].x-p[j].x);
        double ang2 = acos(_dis(p[i], p[j])/2);
        v.push_back( Label(ang1-ang2, true) );
        v.push_back( Label(ang1+ang2, false));
      }
      sort(v.begin(), v.end());
      int tmp = 1;
      for(int Size = v.size(), j = 0; j < Size; j++) {
        if(v[j].in) tmp++;
        else tmp--;
        ans = max(ans, tmp);
      }
    }
    printf("%d\n",ans);
  }
  return 0;
}

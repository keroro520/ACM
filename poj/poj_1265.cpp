/*
  ���㼸��  pick���� blabla
http://blog.sina.com.cn/s/blog_6635898a0100mjn1.html
http://blog.csdn.net/tsaid/article/details/7096631

���⣺��һ��ƽ��ֱ������ϵ�ڣ���һ��������Ϊ����Ķ���Σ���1.�������εı������ǵ������ж��ٸ���2.���������ڲ��������ж��ٸ���3.�������ε������

˼·�������Ķ�������������pick������������������ͱ��ϵĵ���������pick�������ڲ��ĵ�����

pick������һ��ƽ��ֱ������ϵ�ڣ�������Ϊ����ļ򵥶���Σ������߲����棩�����ڲ�������Ϊa�����ı��ϣ��������㣩��������Ϊb�����������S = a+b/2-1��
          S = a+b/2-1
����ϵĵ���Ҳ��һ������Ҫ�Ľ��ۣ�������Ϊ������߶Σ����ǵ�������ΪGCD(dx,dy)�����У�dxdy�ֱ�Ϊ�߶κ���ռ�ĵ���������ռ�ĵ��������dx��dyΪ0���򸲸ǵĵ���Ϊdy��dx��

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

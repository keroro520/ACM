/*
  ���㼸�� �� ���ĸ��� ��λԲ����ܸ���ƽ���϶��ٸ���
  ���⣺��λԲ����ܸ���ƽ���϶��ٸ���
  ˼·����ö��һ���㣬��ö��������������С��2�ĵ㣬�����Ϳ�������ཻ���������л���������������
    ɢ�������淽���Լ����ǣ����򣬾���������Ǵ�������һ�λ����������Ҳ���Ǵ���
    Ps���󽻵�ʱ������һ������ķ������Ǿ������2��Բ�ĵ�б�ʲ���arctan������ĽǶȣ��ڱ�
    ��Բ�ľ�/2��б����R��
    �������ǵ�ʱ�򣬲�����ö�ٵ�Բ�� i->j ��������������� j->i �������������Ϊ i->j ����
    ������ȫ�ж�Բ�ķ����ڼ��������ʱ������


  ���涼��ժ����>O<����Ϊ��̫��Ⱑ~~~
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

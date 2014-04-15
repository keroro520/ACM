/*
  求凸包面积

  本来应该1Y的题，因为计算面积时把S[i]写成了p[i]而WA了两次，还是对拍发现错误的=_=
*/
#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;
#define	MAXN	10005
#define EPS 	1e-8
class Point {
	public : double x, y;
	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
} p[MAXN], start, S[MAXN];
int n;
double SQR(double x) { return x * x;}
double _dis(const Point &a, const Point &b)
{
	return sqrt(SQR(a.x-b.x) + SQR(a.y-b.y));
}
int dblcmp(double x)
{
	if(fabs(x) <= EPS) return 0;
	return x > 0 ? 1 : -1;
}
double xmulti(const Point &a, const Point &b)
{
	return a.x*b.y - a.y*b.x;
}
bool turn_left(const Point &a, const Point &b, const Point &c)
{
	return dblcmp(xmulti(c-a, b-a)) < 0;
}
int Graham()
{
	int S_top = 0;
	for(int i = 0; i < min(2, n); i++) S[S_top++] = p[i];
	for(int i = 2; i < n; i++) {
		while(S_top > 1 && !turn_left(S[S_top-2], S[S_top-1], p[i]))
			S_top--;
		S[S_top++] = p[i];
	}
	return S_top;
}
Point Find()
{
	Point tmp(999999999, 999999999);
	for(int i = 0; i < n; i++)
		if((tmp.y > p[i].y) || (dblcmp(tmp.y-p[i].y) == 0 && tmp.x > p[i].x))
			tmp = p[i];
	return tmp;
}
double Area(const Point &a, const Point &b, const Point &c)
{
	return fabs(xmulti(b-a, c-a));
}
int solve()
{
	int len = Graham();
	double area = 0.0;
	for(int i = 1; i < len-1; i++)
		area += Area(S[0], S[i], S[i+1]);
	return (int)(area/(2*50));
}
bool cmp(const Point &a, const Point &b)
{
	int res = dblcmp(xmulti(a-start, b-start));
	if(res) return res > 0;
	return _dis(a, start) <_dis(b, start);
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
		start = Find();
		sort(p, p+n, cmp);

		printf("%d\n", solve());
	}
	return 0;
}

/*
	计算几何  直线相交交点
	题意：个人在路边建造了一栋房子，他希望他的房子被路过这条路的人看见。然而在房子和路之间的障碍会阻挡路人的视线。他想要你计算在这条路上，行人能够完整地看到他的房子的最长的一段连续的路段的长度
	思路：这个题目要注意的地方，就是这些障碍物可能会给在房子的上方、路的下方，并且有的障碍物可能永远挡不住房子，而有的障碍物可能会完全挡住房子
		  我的思路是，先把房子和路的信息记下。然后，在读取每个障碍物信息的时候，计算这个障碍物能够挡住路的哪部分...

	https://euyuil.com/blog/poj-2074-line-of-sight
*/
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define			MAXN		100005
#define			EPS			1e-8
int n;
class Point {
	public : double x, y;
	Point () { }
	Point (double x, double y) : x(x), y(y) { }
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	friend Point operator / (const Point &a, const double k) {
		return Point(a.x / k, a.y / k);
	}
	friend Point operator * (const Point &a, const double k) {
		return Point(a.x * k, a.y * k);
	}
};
class Line {
	public : Point a, b;
	Line () { }
	Line (const Point &a, const Point &b) : a(a), b(b) { }
	Point vec() const {
		return b - a;
	}
} block[MAXN];
class View {
	public :Point p;
	int label;
	friend bool operator < (const View &a, const View &b) {
		return a.p.x < b.p.x;
	}
};
vector<View> view;
Line house, pro;

void init()
{
	view.clear();
}
void fixpoint(Point &p)
{
	p.x = min(p.x, pro.b.x), p.x = max(p.x, pro.a.x);
}
int dblcmp(double x)
{
	if(fabs(x) <= EPS) return 0;
	return x > 0 ? 1 : -1;
}
double xmulti(const Point &a, const Point &b) 
{
	return a.x * b.y - b.x * a.y;
}
Point intersection(const Line &a, const Line &b)
{
	double u = xmulti(a.vec(), Point(b.b - a.b));
	double v = xmulti(a.vec(), Point(b.a - a.b));
	return (b.b * v - b.a * u) / (v - u);
}
int main()
{
	View pf;
	while(scanf("%lf%lf%lf", &house.a.x, &house.b.x, &house.a.y) , dblcmp(house.a.x+house.b.x+house.a.y)) {
		house.b.y = house.a.y;
		scanf("%lf%lf%lf", &pro.a.x, &pro.b.x, &pro.a.y), pro.b.y = pro.a.y;
		scanf("%d", &n);
		init();
		for(int i = 0; i < n; i++) scanf("%lf%lf%lf", &block[i].a.x, &block[i].b.x, &block[i].a.y), block[i].b.y = block[i].a.y;

		for(int i = 0; i < n; i++) {
			if(block[i].a.y >= house.a.y || block[i].a.y <= pro.a.y) continue;
			//if(dblcmp(block[i].a.y - house.a.y) >= 0) continue;
			//if(dblcmp(pro.a.y - block[i].a.y)   >= 0) continue;
			Point ptl = intersection(Line(house.b , block[i].a), pro);
			Point ptr = intersection(Line(house.a , block[i].b), pro);
			fixpoint(ptl), fixpoint(ptr);
			pf.p = ptl, pf.label = 1;  view.push_back(pf);
			pf.p = ptr, pf.label = -1; view.push_back(pf);
		}
		pf.p = pro.b, pf.label = 1, view.push_back(pf);
		sort(view.begin(), view.end());

		int t = 0;
		double ans = 0;
		double pre = pro.a.x;
		for(int i = 0; i < view.size(); i++) {
			//printf("(%.2f %.2f  %d)\n", view[i].p.x, view[i].p.y, view[i].label);
			if(t > 0 && t + view[i].label == 0) {
				pre = view[i].p.x;
			} else if(t == 0) {
				ans = max(ans, view[i].p.x - pre);
			}

			t += view[i].label;
		}

		if(!dblcmp(ans)) puts("No View");
		else printf("%.2f\n", ans);
	}
	return 0;
}

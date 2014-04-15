/*
	计算几何  好题  判断凸包  圆与多边形相交  点到直线的距离

	题意：给出一个多边形和一个圆，问是否是凸多边形，若是则再问圆是否在凸多边形内部

	思路：分3步：
			(1) 判断是否是凸多边形，即凸包判断
			(2) 判断圆点是否在多边形内部
			(3) 判断点到各边的距离是否大于等于半径

			首先，若给的点是顺时针，则reverse()改为逆时针，判断函数anticlockwise()是用叉积来判断的，利用每3个相邻点组成的两条向量的叉积来判断，都应大于等于0
			然后判断圆点是否在内部：利用圆点和多边形每两个相邻点，组成两个向量，判断叉积是否全都大于0（全为逆时针）
			最后判断点到各边的距离，利用叉积求三角形面积，面积除底边得到距离

	http://www.cnblogs.com/rainydays/archive/2011/07/05/2098102.html
*/
double xmulti(const Point &a, const Point &b)
{
	return a.x * b.y - b.x * a.y;
}
bool anticlockwise()
{
	for(int i = 0; i < n; i++)
		if(dblcmp(xmulti(p[(i+1)%n] - p[i], p[(i+2)%n] - p[i])) < 0) return false;
	return true;
}
bool in_convex(const Point &peg)
{
	for(int i = 0; i < n; i++) 
		if(dblcmp(xmulti(p[i] - peg, p[(i+1)%n] - peg)) <= 0) return false;				//两种都可以AC
		//if(dblcmp(xmulti(p[(i+1)%n] - p[i], peg - p[(i+1)%n])) <= 0) return false;
	return true;
}
bool judge(const Point &peg, const double pegRadius)
{
	for(int i = 0; i < n; i++) {
		double area = fabs(xmulti(p[i] - peg, p[(i+1)%n] - peg));
		double dis  = area / _dis(p[i], p[(i+1)%n]);				//由叉积求面积，面积除于底等于高，即距离
		if(dblcmp(dis - pegRadius) < 0) return false;
	}
	return true;
}
bool is_convex_hull()
{
	for(int i = 0; i < n; i++) 
		if(dblcmp(xmulti(p[(i+1)%n] - p[i], p[(i+2)%n] - p[(i+1)%n])) < 0) return false;
	return true;
}
int main()
{
	double pegRadius, pegX, pegY;
	while(scanf("%d%lf%lf%lf", &n, &pegRadius, &pegX, &pegY), n >= 3) {
		for(int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
		if(!anticlockwise()) reverse(p, p+n);

		if(!is_convex_hull()) puts("HOLE IS ILL-FORMED");
		else if(! in_convex(Point(pegX, pegY)) || !judge(Point(pegX, pegY), pegRadius))
			puts("PEG WILL NOT FIT");
		else puts("PEG WILL FIT");
	}
	return 0;
}

#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		2005
#define		ZERO		1e-8		//
class  Point {
	public : double x, y;
	Point () { }
	Point (double x, double y) : x(x), y(y) { }
	Point operator - (const Point &b) const {
		return Point(x - b.x, y - b.y);
	}
} p[MAXN];
int n;

double SQR(double x) { return x * x; }
double _dis(Point &a, Point &b)
{
	return sqrt( SQR(a.x-b.x) + SQR(a.y-b.y) );
}
int  dblcmp(double x)
{
	if(fabs(x) <= ZERO) return 0;
	return x > 0 ? 1 : -1;
}

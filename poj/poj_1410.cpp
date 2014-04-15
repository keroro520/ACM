/*
	计算几何 简单题
	题意：判线段与矩形是否相交，包含也算

	思路：把矩形拆成四条边判线段，包含的话用最大最小值判一下就可以了
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		ZERO		1e-8

struct Point {
	double x, y;
	Point () { }
	Point (double x, double y) : x(x), y(y) { } 
} ;
struct Seg {
	Point a, b;
	Seg() { }
	Seg(double x1, double y1, double x2, double y2) : a(x1, y1), b(x2, y2) { }
} l;
double multi(Point a, Point b, Point c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}
bool inter(Seg A, Seg B)
{
	if((min(A.a.x, A.b.x) > max(B.a.x, B.b.x)) ||
	   (min(A.a.y, A.b.y) > max(B.a.y, B.b.y)) ||
	   (min(B.a.x, B.b.x) > max(A.a.x, A.b.x)) ||
	   (min(B.a.y, B.b.y) > max(A.a.y, A.b.y))) return false;
	double r1 = multi(A.a, A.b, B.a);
	double r2 = multi(A.a, A.b, B.b);
	double r3 = multi(B.a, B.b, A.a);
	double r4 = multi(B.a, B.b, A.b);
	return r1 * r2 <= ZERO && r3 *r4 <= ZERO;
}
int main()
{
	int cases;
	double lx, rx, ty, by;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lf%lf%lf%lf", &l.a.x, &l.a.y, &l.b.x, &l.b.y);
		scanf("%lf%lf%lf%lf", &lx, &ty, &rx, &by);
		if(lx > rx) swap(lx, rx);
		if(by > ty) swap(by, ty);
		if(inter(l, Seg(lx, ty, lx, by)) ||
		   inter(l, Seg(lx, ty, rx, ty)) ||
		   inter(l, Seg(rx, by, lx, by)) ||
		   inter(l, Seg(rx, by, rx, ty)) ||
		   (lx <= min(l.a.x, l.b.x) && max(l.a.x, l.b.x) <= rx && by <= min(l.a.y, l.b.y) && max(l.a.y, l.b.y) <= ty))
		   	puts("T");
		else puts("F");
	}
	return 0;
}

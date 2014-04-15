/*
	计算几何  基础  平行  重合  交点	
	题意：给两个点能够确定一条直线，题目给出两条直线，要求判断出这两条直线的关系：平行，同线，相交。如果相交还要求出交点坐标

	思路：先判重合，再判平行，再求交点
		  判重合：ab与c共线，ab与d共线，即两个叉积为0即重合
		  判平行：如果两直线平行，那么向量p1p2、p3p4也是平等的。即((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x))==0说明向量平等。

	http://blog.csdn.net/dreamvyps/article/details/6162690
*/
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
#define			ZERO		1e-8

class Point {
	public :
	double x, y;
	friend istream & operator >> (istream & in, Point &a) {
		in >> a.x >> a.y;
		return in;
	}
};
class Line {
	public : Point a, b;
} ;
bool zero(double x) { return fabs(x) <= ZERO; }

double multi(Point &a, Point &b, Point &c)
{
	return (a.x - c.x)*(b.y - c.y) - (a.y - c.y)*(b.x - c.x);
}
bool parallel(Line &A, Line &B)
{
	return zero( (A.a.x - A.b.x)*(B.a.y - B.b.y) - (A.a.y - A.b.y)*(B.a.x - B.b.x) );
}
Point intersection(Line &A, Line &B)
{
	Point &a = A.a, &b = A.b, &c = B.a, &d = B.b, r = a;
	double t = ((a.x - c.x)*(c.y - d.y) - (a.y - c.y)*(c.x - d.x))
				/ ((a.x - b.x)*(c.y - d.y) - (a.y - b.y)*(c.x - d.x));
	r.x += (b.x - a.x)*t, r.y += (b.y - a.y)*t;
	return r;
}
int main()
{
	int cases;
	Line l1, l2;
	scanf("%d", &cases);
	puts("INTERSECTING LINES OUTPUT");
	while(cases--) {
		cin >> l1.a >> l1.b;
		cin >> l2.a >> l2.b;
		double r1 = multi(l1.a, l1.b, l2.a), r2 = multi(l1.a, l1.b, l2.b);
		if(zero(r1) && zero(r2)) {
			puts("LINE");
		} else if(parallel(l1, l2)) {
			puts("NONE");
		} else {
			Point res = intersection(l1, l2);
			printf("POINT %.2f %.2f\n", res.x, res.y);
		}
	}
	puts("END OF OUTPUT");
	return 0;
}

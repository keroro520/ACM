/*
	计算几何  好题
	题意：给出n条线段，问是否存在这样一条直线，使得n条线段在这条直线上的投影至少有一个公共点？

	思路：若存在使得n条线段有公共投影，则果公共投影取做直线的垂线，该垂线必定与每条线段相交
		  问题转化成了“是否存在一条直线与n条线段相交”
		  若存在直线与n条线段相交，则必定存在其中一条是经过这些线段的某两个端点

		  到这里就简单了
*/
#include <stdio.h>
#include <math.h>
#define			ZERO		1e-8
#define			MAXN		105
struct Point {
	double x, y;
} ;
struct Line {
	Point a, b;
} line[MAXN];
int n;

inline	double SQR(double x) { return x * x; }
double  dis(Point &a, Point &b)
{
	return sqrt( SQR(a.x-b.x) + SQR(a.y-b.y) );
}
double multi(Point &s, Point &e, Point &o)
{
	return (s.x - o.x)*(e.y - o.y) - (e.x - o.x)*(s.y - o.y);
	//return (e.x - s.x)*(o.y - s.y) - (o.x - s.x)*(e.y - s.y);
}
bool judge(Point &a, Point &b)
{
	if(dis(a, b) <= ZERO) return false;
	for(int i = 1; i <= n; i++) {
		if(multi(a, line[i].a, b) * multi(a, line[i].b, b) > ZERO) return false;
	}
	return true;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) 
			scanf("%lf%lf%lf%lf", &line[i].a.x, &line[i].a.y, &line[i].b.x, &line[i].b.y);
		if(n == 1) {
			puts("Yes!");
			continue;
		}
		bool flag = false;
		for(int i = 1; i <= n && !flag; i++)
			for(int j = i+1; j <= n && !flag; j++)
				if(judge(line[i].a, line[j].a) ||
				   judge(line[i].a, line[j].b) ||
				   judge(line[i].b, line[j].a) ||
				   judge(line[i].b, line[j].b)) {
				   	puts("Yes!");
					flag = true;
					break;
				}
		if(!flag) puts("No!");
	}
	return 0;
}

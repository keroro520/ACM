/*
	计算几何  好题  直线与线段相交

	题意：有一宽度为1的折线管道,上面顶点为(xi,yi),所对应的下面顶点为(xi,yi-1),假设管道都是不透明的,不反射的,光线从左边入口处的(x1,y1),(x1,y1-1)之间射入,向四面八方传播,求解光线最远能传播到哪里(取x坐标)或者是否能穿透整个管道.

	思路：容易知道，要求一条能到达最远的光线，这条光线一定是经过至少两个折线的折点，而且一定是一个上折点，一个下折点。
		  枚举上下折点 + 判断直线(两个折点构成的光线)与线段(折口)是否相交
		  如果在折口i处相交，则最远交点出现在折口i-1到折口i处，那到底是上管壁相交还是下管壁相交呢？不清楚...都计算交点，取最优
*/
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define		MAXN	45
#define		ZERO	1e-8
int n;
struct Point {
	double x, y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
}up[MAXN], down[MAXN];

double xmulti(Point &a, Point &b, Point &c)
{
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

int  dblcmp(double x) 
{
	if(fabs(x) <= ZERO) return 0;
	return x > 0 ? 1 : -1;
}
bool inter(Point &a, Point &b, Point &c, Point &d)
{
	return (dblcmp(xmulti(a, b, c)) * dblcmp(xmulti(a, b, d)) <= 0);	
}
Point  intersection(Point &a, Point &b, Point &c, Point &d)    
{
    Point r = a;
    double t = ((a.x - c.x)*(c.y - d.y) - (a.y - c.y)*(c.x - d.x))
                 / ((a.x - b.x)*(c.y - d.y) - (a.y - b.y)*(c.x - d.x));
    return Point(r.x + (b.x - a.x)*t, r.y + (b.y - a.y)*t);
}

int main()
{
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 1; i <= n; i++) {		//默认已经排好序了
			scanf("%lf%lf", &up[i].x, &up[i].y);
			down[i].x = up[i].x, down[i].y = up[i].y - 1;
		}

		double ans = -999999999;
		bool through_all = false;
		for(int i = 1; i <= n && !through_all; i++)
			for(int j = 1; j <= n && !through_all; j++) {//if(i != j) {
				int k ;
				for(k = 1; k <= n; k++) //if(i != k && j != k)		//直线L最大延伸到第k-1节管子  
					if(!inter(up[i], down[j],  up[k], down[k])) break;
				if(k == n+1) through_all = true;
				if(k <= max(i, j)) continue;

				//由于不清楚L究竟是与第k-1节管子的上管壁还是下管壁相交，因此都计算交点，取最优
				//举例：若实际L是与上管壁相交，当计算下管壁时，得到的是第k-1个下折点，并不会是最优  
				//反之亦同理   
				Point p = intersection(up[i], down[j], up[k], up[k-1]);
				ans = max(ans, p.x);
				p = intersection(up[i], down[j], down[k], down[k-1]);
				ans = max(ans, p.x);
			}
		if(through_all) puts("Through all the pipe.");
		else printf("%.2f\n", ans);
	}
	return 0;
}

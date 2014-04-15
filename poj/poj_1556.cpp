/*
	计算几何+最短路   判断线段相交
	题意：一个正方形密室边长是10，内部有平行y轴方向的n堵墙，每堵墙都有两道门。要从(0,5)走到(10,5)最短距离是多少？

	思路：主要是判断线段是否相交（不包括端点），然后SPFA搞一下
		  估计是模板有问题吧，得这样写才能过，是在试(1, 1, 2, 3, 4)这个数据的时候发现的
			if(line[k].a.x > node[j].x + ZERO) 	//加了这句
				if(multi(node[i], node[j], line[k].a) * multi(node[i], node[j], line[k].b) < 0) return true;
*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#define		MAXN		20*5*5
#define		INF			9999999999.99
#define		ZERO		1e-8
int head[MAXN], Q[MAXN*100];
double d[MAXN];
bool vis[MAXN];
int idx, line_idx, n, edge_num ;
class Point {
	public : double x, y;
	Point() { }
	Point(double x, double y) : x(x), y(y) { }
} node[MAXN*5];
class Line {
	public : Point a, b;
	Line () { } 
	Line (double x1, double y1, double x2, double y2) : a(x1,y1), b(x2,y2) { }
} line[MAXN*5];
class Edge {
	public : int v, next; double w;
} edge[MAXN * MAXN];

void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, double w)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u], edge[edge_num].w = w;
	head[u] = edge_num++;
}

double	SPFA(int s, int t)
{
	for(int i = 1; i <= t; i++) d[i] = INF, vis[i] = false;
	d[s] = 0;
	int cdr = 0, car = 0;
	Q[cdr++] = s;
	while(car != cdr) {
		int u = Q[car++];
		vis[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(d[u] + edge[k].w < d[v]) {
				d[v] = d[u] + edge[k].w;
				if(!vis[v]) {
					vis[v] = true;
					Q[cdr++] = v;
				}
			}
		}
	}
	return d[t];
}
double 	SQR(double x) { return x * x; } 
double 	dis(Point &a, Point &b) { return sqrt( SQR(a.x-b.x) + SQR(a.y-b.y) ); }
bool 	zero(double x) 	{	return ZERO >= fabs(x); 	}
bool  	same(double x, double y) { return zero(x-y); }
double  multi(Point &a, Point &b, Point &c)
{
	//return (a.x - c.x)*(b.y - c.y) - (a.y - c.y)*(b.x - c.x);
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}
bool 	inter(int i, int j)
{
	for(int k = 0; k < line_idx && line[k].a.x < node[i].x; k++) if(line[k].a.x > node[j].x + ZERO) 	//加了这句
		if(multi(node[i], node[j], line[k].a) * multi(node[i], node[j], line[k].b) < 0) return true;
	return false;
}
int main()
{
	double x, y;
	while(scanf("%d", &n), n != -1) {
		
		idx = 0; line_idx = 0;
		node[idx++] = Point(0, 5);
		for(int i = 1; i <= n; i++) {
			double tmp;
			scanf("%lf", &x);
			for(int j = 0; j < 4; j++) {
				scanf("%lf", &y);
				node[idx++] = Point(x, y);
				if(j == 0) line[line_idx++] = Line(x, 0, x, y);
				else if(j == 2) line[line_idx++] = Line(x, tmp, x, y);
				else if(j == 3) line[line_idx++] = Line(x, y, x, 10);
				tmp = y;
			}
		}
		node[idx++] = Point(10, 5);
		//for(int i = 0; i < line_idx; i++) printf("(%.2f  %.2f) (%.2f  %.2f)\n", line[i].a.x,line[i].a.y,line[i].b.x,line[i].b.y);
		init();
		for(int i = 1; i < idx; i++)
			for(int j = 0; j < i; j++) 
				if(!same(node[i].x, node[j].x) && !inter(i, j)) {
					add_edge(j, i, dis(node[i], node[j]));
					//printf("(%.2f %.2f) (%.2f  %.2f)\n",node[j].x,node[j].y, node[i].x,node[i].y);
				}
		printf("%.2f\n", SPFA(0, idx-1));
	}
	return 0;
}

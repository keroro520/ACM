/*
	计算几何  判断两条线段是否相交
	题意：从1-n扔筷子，问最后在最上面有哪几根筷子？即没有其它筷子压在他们上面

	思路：判断线段是否相交

		  vector的erase返回erase后的下一个元素
		  set的erase是void类型....得处理一下...
*/
#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
#define		MAXN		100005
#define		ZERO		1e-8
set<int> S;
struct Point {
	double x, y;
};
struct Seg	{
	Point a, b;
} stick[MAXN];
int n;

double multi(Point &a, Point &b, Point &c)
{
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}
bool inter(Seg &A, Seg &B)
{
	if(min(A.a.x, A.b.x) > max(B.a.x, B.b.x) ||
	   min(A.a.y, A.b.y) > max(B.a.y, B.b.y) ||
	   min(B.a.x, B.b.x) > max(A.a.x, A.b.x) ||
	   min(B.a.y, B.b.y) > max(A.a.y, A.b.y)) return false;
	double r1 = multi(A.a, A.b, B.a);
	double r2 = multi(A.a, A.b, B.b);
	double r3 = multi(B.a, B.b, A.a);
	double r4 = multi(B.a, B.b, A.b);
	return r1*r2 <= ZERO && r3*r4 <= ZERO;
}
void solve(Seg & l)
{
	for(set<int> :: iterator it = S.begin(); it != S.end(); ) 
		if(inter(l, stick[*it])) {
			set<int> :: iterator tmp = it;
			if(it == S.begin()) {
				S.erase(tmp);
				it = S.begin();
			} else {
				it--;
				S.erase(tmp);
				it++;
			}
		} else it++;
}
int main()
{
	while(scanf("%d", &n) != EOF && n) {
		S.clear();
		for(int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf%lf", &stick[i].a.x, &stick[i].a.y, &stick[i].b.x, &stick[i].b.y);
			solve(stick[i]);
			S.insert(i);
		}
		printf("Top sticks: ");
		for(set<int> :: iterator it = S.begin(); it != S.end(); ) {
			printf("%d", *it);
			if(++it == S.end()) puts(".");
			else printf(", ");
		}
	}
	return 0;
}

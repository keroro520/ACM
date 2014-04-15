/*
	计算几何  好题  极角排序
	题意：从y坐标最低的点出发，每次只能向左转，并且不能与之前走过的路相交，问最多能经过多少个点。
		这其实就是一个对每个点，找求最小极角的问题首先判断当前的角与堆栈顶部的两个角的夹角是否成左旋，然后找与当前栈顶的点构成的直线角度最小的点入栈，然后重复上面的步骤，直到没有满足条件的点为止


	思路：极角排序用叉积，因为这里保证180.....
*/
bool cmp_By_Angle(const Point &a, const Point &b) {
	int res = xmulti(cur, a, b);
	if(res > 0) return true;
	else if(res < 0) return false;
	else return dis(a,cur) < dis(b, cur);
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%d%d", &p[i].idx, &p[i].x, &p[i].y);
		sort(p+1, p+1+n, cmp_By_Y);
		cur = p[1];
		printf("%d", n);
		printf(" %d", cur.idx);
		for(int i = 2; i <= n; i++) {
			sort(p+i, p+1+n, cmp_By_Angle);
			cur = p[i];
			printf(" %d", cur.idx);
		}
		puts("");
	}
	return 0;
}

#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define			MAXN		15
struct Point {
	int idx, x, y;
}p[MAXN], cur;
int n;

inline	double	SQR(double x) { return x * x; }
double dis(const Point &a, const Point &b)
{
	return sqrt( SQR((a.x - b.x)*1.0) + SQR((a.y - b.y)*1.0) );
}
int xmulti(const Point &a, const Point &b, const Point &c) {
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}
bool cmp_By_Y(const Point & a, const Point &b) {
	return a.y < b.y;
}

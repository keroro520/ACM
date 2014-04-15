/*
	简单二分 + 叉积判断  简单计算几何
	题意：给出若干不相交的线段，这些线段的y1,y2座标都是相同的。再给出询问(x,y)，判断(x,y)的落在哪个区间

	思路：二分 + 叉积判断
 		  得到(s-o)和(e-o)的叉积
	      r>0,e在矢量os的逆时针方向；r=0三点共线；r<0,e在矢量os的顺时针方向
*/
#include <stdio.h>
#include <string.h>
#define		MAXN		5005
#define		ZERO		0.00000001
int cnt[MAXN];
struct Point {
	int x, y;
};
struct Line {
	Point a, b;
} line[MAXN];
int n, m;
int Multi(Point &s, Point &e, Point &o) 		
{
/* 	得到(s-o)和(e-o)的叉积
	r>0,e在矢量os的逆时针方向；r=0三点共线；r<0,e在矢量os的顺时针方向 */
	return (s.x - o.x)*(e.y - o.y) - (e.x - o.x)*(s.y - o.y);
}
void Find(Point &a)
{
	int l = 1, r = n, ans = n+1, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(Multi(a, line[mid].a, line[mid].b) < 0) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cnt[ans-1]++;
}
int main()
{
	int x1, x2, y1, y2, t1, t2;
	while(scanf("%d%d", &n, &m) != EOF && n) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		for(int i = 1; i <= n; i++) {
			scanf("%d%d", &t1, &t2);
			line[i].a.x = t1, line[i].a.y = y1;
			line[i].b.x = t2, line[i].b.y = y2;
		}
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < m; i++) {
			Point tmp;
			scanf("%d%d", &tmp.x, &tmp.y);
			Find(tmp);
		}
		for(int i = 0; i <= n; i++) printf("%d: %d\n", i, cnt[i]);
		puts("");
	}
	return 0;
}

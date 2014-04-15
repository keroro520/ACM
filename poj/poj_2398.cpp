/*
	简单二分 + 叉积判断  简单计算几何
	题意：给出若干不相交的线段，这些线段的y1,y2座标都是相同的。再给出询问(x,y)，判断(x,y)的落在哪个区间

	思路：跟poj_2138少许不同点是：可能有超边界的点；要给这些线段排一下序
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN		5005
#define		ZERO		0.00000001
int cnt[MAXN];
struct Point {
	int x, y;
};
struct Line {
	Point a, b;
	friend bool operator < (const Line &l1, const Line &l2) {
		return max(l1.a.x,l1.b.x) < max(l2.a.x,l2.b.x);
	}
} line[MAXN];
int n, m;
int Multi(Point &s, Point &e, Point &o) 		
{
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
int num[MAXN];
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
		sort(line+1, line+1+n);
		memset(cnt, 0, sizeof(cnt));
		memset(num, 0, sizeof(cnt));
		for(int i = 0; i < m; i++) {
			Point tmp;
			scanf("%d%d", &tmp.x, &tmp.y);
			if(tmp.x < x1 || x2 < tmp.x || y1 < tmp.y || tmp.y < y2) continue;		//出界
			Find(tmp);
		}
		for(int i = 0; i <= n; i++) num[ cnt[i] ] ++;
		puts("Box");
		for(int i = 1; i <= n; i++) if(num[i]) printf("%d: %d\n", i, num[i]);
	}
	return 0;
}

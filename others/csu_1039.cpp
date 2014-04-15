/*
	二分 好题
	题意：给出N个凹凸曼的座标，N个小怪兽的座标，问最近的凹凸曼和小怪兽的距离

	思路：凹凸曼的点按x座标排好序
		  对于小怪兽i，二分查找找到(bi.x - ans, bi.x + ans) 这个区间，然后就只要枚举这个区间更新最优值就行了
*/
//http://acm.csu.edu.cn/OnlineJudge/problem.php?cid=2036&pid=2
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define		MAXN		100005

class Node {
	public :int x, y;
	friend bool operator < (const Node &a, const Node &b) {
		return a.x < b.x;
	}
} a[MAXN], b[MAXN];
int n;
double SQR(double x) { return x * x; }
double _dis(Node &a, Node &b)
{
	return sqrt( SQR((a.x-b.x)*1.0) + SQR((a.y-b.y)*1.0) );
}
int Find_Min(int x)
{
	int l = 0, r = n - 1, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(b[mid].x <= x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}
int Find_Max(int x)
{
	int l = 0, r = n - 1, ans = n - 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(b[mid].x >= x) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}
int main()
{
	int A, B;
	while(scanf("%d%d%d", &n, &A, &B) != EOF) {
		for(int i = 0; i < n; i++) scanf("%d%d", &a[i].x, &a[i].y);
		for(int i = 0; i < n; i++) scanf("%d%d", &b[i].x, &b[i].y);
		sort(a, a+n);
		sort(b, b+n);
		double ans = 99999999999;
		for(int i = 0; i < n; i++) {
			for(int j = Find_Min(max(0, (int)(a[i].x-ans)+1)); j <= Find_Max((int)(a[i].x+ans)-1); j++)
				ans = min(ans, _dis(a[i], b[j]));
		}
		printf("%.3lf\n", ans/(A+B));
	}
	return 0;
}

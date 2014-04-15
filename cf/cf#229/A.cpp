#include <stdio.h>
#include <algorithm>
using namespace std;
struct Alarm {
	int x, y;
} a[100005];
bool cmp_x(const Alarm &a, const Alarm &b) {
	return a.x < b.x;
}
bool cmp_y(const Alarm &a, const Alarm &b) {
	return a.y < b.y;
}
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d %d", &a[i].x, &a[i].y);
	sort(a, a+n, cmp_x);
	int ans = 1, best = 0;
	for(int i = 1; i < n; i++) 
		if(a[i].x != a[i-1].x) ans ++;
	best = ans , ans = 1;
	sort(a, a+n, cmp_y);
	for(int i = 1; i < n; i++) 
		if(a[i].y != a[i-1].y) ans ++;
	printf("%d\n", min(ans, best));
	return 0;
}

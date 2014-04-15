#include <stdio.h>
#include <algorithm>
using namespace std;
typedef	long long		ll;

struct Node {
	ll num;
	int idx;
}a[300005];
ll ans[300005];
int n;
bool cmp(const Node & a, const Node & b) {
	return a.num < b.num;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%I64d", &a[i].num), a[i].idx = i;
	sort(a, a+n, cmp);
	ll tmp = 0;
	for(int i = 0; i < n; i++) {
		tmp = max(a[i].num, tmp);
		ans[a[i].idx] = tmp ++;
	}
	for(int i = 0; i < n; i++) printf("%I64d ", ans[i]);
	return 0;
}

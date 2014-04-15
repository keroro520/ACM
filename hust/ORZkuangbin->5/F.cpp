#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN		100005
int n ,query ,ans[MAXN], next[MAXN];
struct Segment {
	int l, r, len, idx;
} a[MAXN];
struct Quetion {
	int num, idx;
} q[MAXN];
bool cmp_by_len(const Segment & a, const Segment & b) {
	return a.len < b.len;
}
bool cmp_by_num(const Quetion & a, const Quetion & b) {
	return a.num < b.num;
}
int Find_greater(int x, int l, int r)
{
	int ans = query, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(q[mid].num >= x) r = mid - 1, ans = mid;
		else			l = mid + 1;
	}
	return ans;
}
int Find_less(int x, int l, int r)
{
	int ans = -1, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(q[mid].num <= x) l = mid + 1, ans = mid;
		else 			r = mid - 1;
	}
	return ans;
}

int Find_next(int x)
{
	return x == next[x] ? x : next[x] = Find_next(next[x]);	
}
void solve(int left, int right, int ID)
{
	int l = Find_greater(left, 0, query-1), r = Find_less(right, 0, query-1);

	while(l <= r) {
		if(ans[ q[l].idx ] == -1) ans[ q[l].idx ] = ID, next[l] = l+1;
		
		l = Find_next(l);
	}
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) scanf("%d %d", &a[i].l, &a[i].r), a[i].len = a[i].r - a[i].l + 1, a[i].idx = i+1;
		sort(a, a+n, cmp_by_len);
		scanf("%d", &query);
		for(int i = 0; i < query; i++) scanf("%d", &q[i].num), q[i].idx = i;
		sort(q, q+query, cmp_by_num);

		for(int i = 0; i <= query; i++) next[i] = i;
		memset(ans, -1, sizeof ans);

		for(int i = 0; i < n; i++) {
			solve(a[i].l, a[i].r, a[i].idx);
		}
		for(int i = 0; i < query; i++) printf("%d\n", ans[i]);
	}
	return 0;
}

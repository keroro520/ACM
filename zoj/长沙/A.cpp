#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		100005
typedef		long long		ll;
ll p[MAXN], s[MAXN];
int Min[MAXN];
int n;

int bit_find(ll x, ll * p, int l)
{
	int r = n, ans = l, mid;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(p[mid] <= x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}
int main()
{
	int cases, m; ll x;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; i++) scanf("%lld %lld", &s[i], &p[i]);
		int _Min = n + 1;
		s[_Min] = (1LL << 30), p[_Min] = (1LL << 30);
		for(int i = n; i >= 1; i--) {
			Min[i] = _Min;
			if(s[i] * p[i] <= s[_Min] * p[_Min]) _Min = i;
		}
		
		while(m--) {
			scanf("%lld", &x);
			int pos = bit_find(x, s, 1);
			ll ans = x * p[pos];
			ans = min(ans , s[Min[pos]] * p[Min[pos]]);
			printf("%lld\n", ans);
		}
	}
	return 0;
}

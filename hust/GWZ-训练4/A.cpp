#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MOD = 31536000;
#define MAXN 100005

struct Obj {
	ll A, B;
} obj[MAXN];
int n;

bool cmp(const Obj & a, const Obj & b) {
	ll res = a.A*b.B - b.A*a.B;
	return res < 0;
}
int main()
{
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 0; i < n; i++) scanf("%lld %lld", &obj[i].A, &obj[i].B);
		sort(obj, obj+n, cmp);
		ll ans =  0, sum = 0;
		for(int i = 0; i < n; i++) {
			ans = (ans + sum * obj[i].B + obj[i].A) % MOD;
			sum = (sum + obj[i].A + obj[i].B*sum) % MOD;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

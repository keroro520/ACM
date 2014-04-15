#include <stdio.h>
#include <algorithm>
using namespace std;
long long a[100005], sum[100005], n;
long long Gcd(long long a, long long b)
{
	return b == 0 ? a : Gcd(b, a % b);
}
int main()
{
	scanf("%I64dd", &n);
	for(int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
	sort(a+1, a+n+1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + a[i];
	long long ans = sum[n];
	for(int i = 1; i <= n; i++)
		ans += 2 * (a[i] * (i-1) - sum[i-1]);
	long long gg = Gcd(max(ans,n), min(ans, n));
	//printf("#  %I64d\n", gg);
	ans /= gg, n /= gg;
	printf("%I64d %I64d\n", ans, n);
	return 0;
}

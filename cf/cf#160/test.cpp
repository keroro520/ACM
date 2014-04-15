#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		55
long long dp[MAXN][MAXN];
int a[MAXN];
int n;
double ans;
long long dfs(int pos, int p)
{
	if(pos == n) return n;
	if(dp[pos][p] != -1) return dp[pos][p];
	long long res = 0;
	for(int i = pos; i < n; i++)
		if(p < a[i]) res += pos;
		else res += dfs(i+1, p-a[i]);

	return dp[pos][p] = res;
}
void fac(int n) { 
	for(int i = 1; i <= n; i++) 
		ans /= i;

	long long tot = 1;
	for(int i = 1; i <= n; i++) tot *= i;
	printf("tot : %lld\n", tot);
}
int main()
{
	memset(dp, -1, sizeof(dp));
	int sum = 0, p;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]), sum += a[i];
	scanf("%d", &p);
	if(p >= sum) {
		printf("%d\n", n);
		return 0;
	}
	sort(a, a+n);
	ans = (double)dfs(0, p);
	printf("%lld\n", (long long)ans);
	fac(n);
	printf("%.13f\n", ans);
	return 0;
}

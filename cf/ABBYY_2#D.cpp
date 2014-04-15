//WA
#include <stdio.h>
#include <algorithm>
using namespace std;
#define	MAXN  100005
long long MOD;
int n, m;
long long a[MAXN], b[MAXN], sum[MAXN], after[MAXN];
int main()
{
	//freopen("in.txt", "r", stdin);
	scanf("%d%d%I64d", &n, &m, &MOD);
	for(int i = 1; i <= n; i++) scanf("%I64d", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%I64d", &b[i]);
	sum[0] = 0;
	for(int i = 1; i <= m; i++) sum[i] = (sum[i-1] + b[i]) % MOD;
	after[m+1] = 0;
	for(int i = m; i >= 1; i--) after[i] = (after[i+1] + b[i]) % MOD;

	for(int i = 1; i <=m-1; i++) a[i] = (a[i] + sum[i]) % MOD;

	for(int i = m; i <= n-m+1; i++) {
		//for(int s = max(i-m+1, 0); s <= min(i, n-m); s++) {
			a[i] = (a[i] + sum[m]) % MOD;
		//}
	}

	for(int i = n-m+2; i <= n; i++)
		a[i] = (a[i] + after[(i-(n-m+1))+1]) % MOD;

	for(int i = 1; i <= n; i++) printf("%I64d ", a[i]);
	return 0;
}

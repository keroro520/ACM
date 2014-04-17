#include <stdio.h>
#define		MAXN		1005
typedef		long long 		ll;
#define		MOD				1000000007
int p[MAXN];
ll out[MAXN];
int n;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &p[i]);

	for(int i = 1; i <= n; i++) {
		if(p[i] == i) { out[i] = 2; continue; }
		out[i] = (2 + out[p[i]]) % MOD;
		for(int j = p[i]+1; j < i; j++) out[i] = (out[i] + out[j]) % MOD;
	}

	ll ans = 0;
	for(int i = 1; i <= n; i++) ans = (ans + out[i]) % MOD;
	printf("%I64d\n", ans);
	return 0;
}

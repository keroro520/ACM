#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
typedef		long long		ll;
#define		MAXN		1005
#define		MOD			1000003

int n, cnt[MAXN], c[MAXN][MAXN];
void divide(int x)
{
	for(int i = 0; i <= 31; i++) cnt[i] += ((x >> i) & 1);
}
void init()
{
	c[0][0] = c[1][0] = c[1][1] = 1;
	for(int i = 2; i <= 1000; i++) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j++)
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % MOD;
	}
}
int main()
{
	init();
	int x;
	while(scanf("%d", &n) != EOF) {
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			divide(x);
		}
		for(int k = 1; k <= n; k++) {
			ll sum = 0;
			for(int bit = 31; bit >= 0; bit--) {
				for(int i = 1, oo = min(cnt[bit], k); i <= oo; i += 2)
					sum += (ll)c[cnt[bit]][i] * c[n-cnt[bit]][k-i];
				if(bit) sum *= 2;
				sum %= MOD;
			}
			printf("%I64d%c", sum % MOD, k == n ? '\n' : ' ');
		}
	}
	return 0;
}

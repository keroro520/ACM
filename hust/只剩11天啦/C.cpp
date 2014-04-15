#include <stdio.h>
typedef long long ll;

int main()
{
	int cases, Cas = 0 ;
	scanf("%d", &cases);
	while(cases--) {
		printf("Case #%d: ", ++Cas);
		ll sum = 0, x, M;
		for(int i = 0; i < 5; i++) scanf("%lld", &x), sum += x;
		scanf("%lld", &M);
		if(sum >= M) puts("0");
		else if(sum <= 0) puts("-1");
		else {
			int ans = 0;
			while(true) {
				if(sum >= M || sum <= 0) { printf("%d\n", ans); break; }
				sum <<= 1;
				ans++;
			}
		}
	}
	return 0;
}

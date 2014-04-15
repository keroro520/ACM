#include <stdio.h>
#include <algorithm>
#include <functional>
using namespace std;
typedef		long long 	ll;
ll a[4];

int main()
{
	while(scanf("%lld %lld %lld", &a[0], &a[1], &a[2]) != EOF) {
		ll ans = 0;
		sort(a, a+3, greater<ll>() );

		if(a[0] + a[1] + a[2] <= 3) { printf("%lld\n", a[0]+a[1]+a[2] <= 1 ? 0 : (a[0]+a[1]+a[2] == 3 ? 3 : 1)); continue; }

		if(a[0] > 1 && a[1] > 1 && a[2] > 1) {
			ans = 15;
			ans += (a[0]+a[1]+a[2] - 6) * 6;
		} else if(a[1] == 0 && a[2] == 0) {
			ans = 1;
			ans += (a[0]-2) * 2;
		} else if(a[1] && a[2] == 0) {
			if(a[1]	== 1) {
				ans = 6 + (a[0]-3) * 3;
			} else {
				ans = 6 + (a[0]+a[1]-4) * 4;
			}
		} else if(a[0]+a[1]+a[2] == 4) ans = 6;
		  else if(a[0]+a[1]+a[2] == 5) ans = 10;
		  else if(a[1] == 1) ans = 6 + (a[0]-2)*4;
		  else if(a[1] >= 2) ans = 10 + (a[0]+a[1]-4)*5;
		else while(true);	
		printf("%lld\n", ans);
	}
	return 0;
}

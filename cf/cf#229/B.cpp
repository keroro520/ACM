#include <stdio.h>
typedef long long ll;
ll a[100005], b[100005];
int n;
int main()
{
	ll ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%I64d", &a[i]);
	for(int i = 0; i < n; i++) scanf("%I64d", &b[i]);
	for(int i = 0; i < n; i++) 
		if(b[i] == 1) ans --;
		else if(b[i] <= a[i] * 2) ans += b[i]/2 * (b[i]-b[i]/2);
		else ans --;
	printf("%I64d\n", ans);
	return 0;
}



int n, K;
bool check(ll c)
{
	for(int i = 2; i <= n; i++) {
		
	}
}
int main()
{
	scanf("%d %d", &n, &K);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);

	ll l = 0, r = 2000000000, ans = 0, mid ;
	while(l <= r) {
		for(int i = 1; i <= n; i++) L[i] = R[i] = i;
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}

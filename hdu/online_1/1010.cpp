#include <stdio.h>
#define		MAXN		100005
int n;
int a[MAXN];
long long calc(int x);
int main()
{
	int Cas = 0, cases, m;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		int s = 1, mid = 1;
		int sum = 0;
		long long ans = 0;
		for(int i = 1; i <= n; i++) {
			sum |= a[i];
			if(sum >= m) {
				ans += (long long)(mid-s)*(i-1-mid+1) + calc(i-1-mid+1);
				sum = 0; mid = i;
				if(a[i] >= m) {mid = i+1; s = i+1; continue;}
				int tmp = 0;
				for(int j = i; ; j--) {
					tmp = sum;
					sum |= a[j];
					if(sum >= m) {
						s = j+1;
						break;
					}
				}
				sum = tmp;
			}
		}
		if(sum < m) ans += (long long)(mid-s)*(n-mid+1) + calc(n-mid+1);
		for(int i = 1; i <= n; i++) ans += (a[i] < m);
		printf("Case #%d: %I64d\n", ++Cas, ans);
	}
	return 0;
}
long long calc(int x)
{
	if(x < 2) return 0;
	return (long long)x * (long long)(x-1) / 2;
}

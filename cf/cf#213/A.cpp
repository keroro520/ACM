#include <stdio.h>

bool check(long long  x, long long K)
{
	long long tmp2 = 0, tmp=0;
	while(x) {
		int y = x % 10;
		//if(y > K) return false;
		if(y <= K) tmp |= (1LL << y);
		x /= 10;
	}
	for(int i = 0; i <= K; i++) tmp2 |= (1 << i);
	return tmp2 == tmp;
}
int main()
{
	int n, ans = 0;
	long long x, K;
	scanf("%d %I64d", &n, &K);
	for(int i = 0; i < n; i++) {
		scanf("%I64d", &x);
		ans += check(x, K);
	}
	printf("%d\n", ans);
	return 0;
}

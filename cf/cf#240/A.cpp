// 简单构造
// 可是...trick好多，WA惨

#include <stdio.h>

int main()
{
	int n, K;
	scanf("%d %d", &n, &K);
	if(n == 1 && K == 0) { puts("1"); return 0; }
	if(n == 1 || n/2 > K) { puts("-1"); return 0; }
	int rem = K - (n-2)/2;
	int best = 2*rem+1 > n ? 2*rem + 1 : n;
	for(int i = 1; i <= (n - (n&1))-2; i += 2) 
		if(i == rem || i+1 == rem) printf("%d %d ", best, best+1);
		else if(i == rem*2 || i+1 == rem*2) printf("%d %d ", best+2, best+3);
		else printf("%d %d ", i, i+1);
	printf("%d %d ", rem, rem*2);
	if(n&1) printf("%d\n", best+4); else puts("");
	return 0;
}

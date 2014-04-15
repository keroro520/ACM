#include <stdio.h>

int main()
{
	int ans = 0, rest = 0, tmp = 0, a, b;
	scanf("%d %d", &a, &b);
	while(a) {
		ans += a;
		
		tmp = rest;
		rest = (a+rest) % b;
		a = (a+tmp) / b;
	}
	printf("%d\n", ans);
	return 0;
}

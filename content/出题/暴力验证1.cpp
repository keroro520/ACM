/*
	暴力验证程序 题1

	数位DP
	1-n的数中各个数位之和不超过p的数有多少？
*/
#include <stdio.h>

int calc(int x)
{
	int sum = 0;
	while(x) {
		sum += x % 10;
		x /= 10;
	}
	return sum;
}
int main()
{
	int ans = 0, n, p;
	scanf("%d%d", &n, &p);
	for(int i = 0; i <= n; i++) if(calc(i) <= p) ans++;
	printf("%d\n", ans);
	return 0;
}

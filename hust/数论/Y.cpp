/*
	WA 
	神题  赛后建议做做这道挑战思维束缚的题 现在还是不花时间做了

	看strainger得到题解吧
*/
#include <stdio.h>

int main()
{
	int n; double t;
	while(scanf("%d %lf", &n, &t), n) {
		double p0 = (1 + t) / 2, p = 1;
		double ans = 1;
		for(int i = 1; i <= n; i++) {
			p *= p0;
			ans += p * (1LL << i);
		}
		printf("%.3f\n", ans);
	}
	return 0;
}

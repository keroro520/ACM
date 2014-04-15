#include <stdio.h>
#include <math.h>

int main()
{
	int cases;
	double x;
	scanf("%d", &cases);
	while(cases--) {
		printf("$");
		double sum = 0;
		for(int i = 0 ; i < 12; i++) scanf("%lf", &x), sum += x;
		sum /= 12;
		long long tmp = (long long) round(sum * 100) ;
		if(tmp % 100 == 0) printf("%I64d\n", tmp/100);
		else if(tmp % 10 == 0) printf("%.1f\n", sum);
		else printf("%.2f\n", sum);
	}
	return 0;
}

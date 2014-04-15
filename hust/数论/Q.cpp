/*
	概率论  简单题
	题意：N个人按顺序猜奖，每个人每次猜中的机率都为p。第i号猜完后轮第i+1号，第N号猜完后轮1号，猜到有某个人猜中即停止
		  问I号人猜中的概率

	思路：乱搞搞过了...ans = (1-p)^(I-1) * p  +  (1-p)^(I-1+N) * p  +  (1-p)^(I-1+2N) * p ... 
*/
#include <math.h>
#include <stdio.h>
#define			EPS			1e-6

int main()
{
	int cases, n, I;  double p;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %lf %d", &n, &p, &I);
		double ans = 0;  int step = 0;
		while(true) {
			double t = pow(1 - p, I-1+step*n) * p;
			if(t <= EPS) break;
			ans += t,  step ++;
		}
		printf("%.4f\n", ans);
	}
	return 0;
}

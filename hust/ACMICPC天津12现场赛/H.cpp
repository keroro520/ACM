#include <stdio.h>

int main()
{
	int cases; double x,y,p,q;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lf %lf %lf %lf" , &x, &y, &p, &q);
		double t1 = p * q * (x + y) + (1 - q) * x;
		double t2 = p * (1 - q)*(x+y) + q * y;
		if(t1 >= t2) printf("tiger %.4f\n", t1);
		else 	     printf("wolf %.4f\n",  t2);
	}
	return 0;
}

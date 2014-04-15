/*
	三分  中位数定理  好题
*/
//sgu 524
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
//#define			ZERO		1e-8
#define			MAXN		405
const double ZERO = 1e-8;
double a[MAXN], y[MAXN], x0;
int n;

double calc(double d)
{
	for(int i = 1; i <= n; i++) {
		y[i] = a[i] - (i-1)*d;
	}
	sort(y+1, y+1+n);
	x0 = y[(n+1)/2];
	double sum = 0;
	for(int i = 1; i <= n; i++)
		sum += fabs(y[i] - x0);
	return sum;
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; i ++) scanf("%lf", &a[i]);
		double l = 0, r = 100000, lmid, rmid;
		while(r - l >= ZERO) {
			double gap = (r - l)/3;
			lmid = l + gap, rmid = r - gap;
			if(calc(lmid) + ZERO< calc(rmid)) r = rmid; 
			else l = lmid;
		}
		double ans = calc(l);
		printf("%.4f\n", ans);
		for(int i = 1; i <= n; i++) printf("%.7f%c", x0+(i-1)*l, i == n? '\n' : ' ');
	}
	return 0;
}

/*
	水题
*/
//sgu 152
#include <stdio.h>
#define		MAXN		10005
const double ZERO = 1e-8;
int b[MAXN], a[MAXN];
int n;
int main()
{
	while(scanf("%d", &n) != EOF) {
		double tot = 0;
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), tot += a[i];
		int sum = 0;
		for(int i = 0; i < n; i++) b[i] = (int)((a[i]*100*1.0)/tot), sum += b[i];
		sum = 100 - sum;
		for(int i = 0; i < n && sum; i++) 
			if(a[i]*100*1.0/tot > b[i] + ZERO) b[i]++, sum--;
		for(int i = 0; i < n; i++) printf("%d%c", b[i], i == n-1? '\n' : ' ');
	}
	return 0;
}

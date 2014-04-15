#include <algorithm>
#include <math.h>
#include <stdio.h>
using namespace std;
#define		EPS		1e-7

int X, Y, ans;
double K1, K2;

void dfs(int a, double b, int sum)
{

	double k = b/a;
	if(K1 <= k && k < K2) { ans = sum + X - a; return ; }

	for(int i = floor(a*K1-b); ; i++) {
		double tmp = (b+i)/a;
		if(tmp >= K2) { 
			double bbb = (b+i-1), aaa = a;
			dfs(aaa+1, bbb+bbb/a, sum + i-1+1); 
			break; 
		}
		if(K1 <= tmp && tmp < K2) { dfs(a, b+i, sum+i); break; }
	}
}
int main()
{
	while(scanf("%d %d", &X, &Y) != EOF) {
		K1 = Y*1.0/X, K2 = (Y+1)*1.0/X;

		if(X > Y) { puts("-1"); continue; }
		dfs(1, 1, 0);
		printf("%d\n", ans);
	}
	return 0;
}

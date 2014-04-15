#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
#define		inf			999999999
#define		EPS			1e-9
struct Function {
	int a, b, c;
} f[MAXN];
int n;

double calc(double x)
{
	double ans = -inf;
	for(int i = 0; i < n; i++) 
		ans = max(ans, f[i].a*x*x + f[i].b*x + f[i].c);
	return ans;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) scanf("%d %d %d", &f[i].a, &f[i].b, &f[i].c);
		double l = 0, r = 1000, lmid, rmid;
		while(r - l > EPS) {
			double t = (l + r) / 3;
			//lmid = l + t, rmid = r - t;						//为什么这样三分是错的...
			lmid = (l + r) / 2, rmid = (lmid + r) / 2;
			double f1 = calc(lmid), f2 = calc(rmid);
			if(f1 > f2) l = lmid; else r = rmid;
		}
		printf("%.4f\n", calc(l));
	}
	return 0;
}

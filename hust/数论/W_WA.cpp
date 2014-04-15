//WA
//连样例都没过
//我只想知道为什么我的是错的？我的算法实际上是计算什么量？
//for(int i = 0; i < n; i++) a[i] = a[i] / sum; 这一句又会在什么情况下使用？
#include <stdio.h>
#define			MAXN		21

int _std, n;
double ans, debug;
double a[MAXN], res[MAXN];

void dfs(int cur, int rest, double pre)
{
	if(rest < 0 || n - cur < rest) return ;
	if(cur == n) {
		ans += pre;
		debug += pre;
		return ;
	}

	if(cur == _std) { dfs(cur+1, rest, pre*a[_std]); return ;}
	dfs(cur+1, rest-1, pre*a[cur]);
	dfs(cur+1, rest  , pre*(1-a[cur]));
}
int main()
{
	int r, Cas = 0;
	while(scanf("%d %d", &n, &r) , n || r) {
		printf("Case %d:\n", ++Cas);
		double sum = 0;
		for(int i = 0; i < n; i++) scanf("%lf", &a[i]);//, sum += a[i];
		//for(int i = 0; i < n; i++) a[i] = a[i] / sum;
		debug = 0;
		for(int i = 0; i < n; i++) {
			_std = i;
			ans  = 0;
			dfs(0, r-1, 1);
			res[i] = ans;
			//printf("%.6f\n", ans );
		}
		for(int i = 0; i < n; i++) printf("%.6f\n", res[i] / debug);
	}
	return 0;
}

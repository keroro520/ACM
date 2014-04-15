/*
	概率论  分组背包  母函数？
	题意：扔N颗骰子，问总和不少于x的概率

	思路：这不是赤果果的分组背包么  怎么会在数论场？难道说还能用母函数做？or else ？
		 
		  就是“每组必须取一个且仅取一个”的分组背包，hdu_3303是“每组至少取一个”的分组背包
*/
#include <stdio.h>
#include <string.h>
typedef 	long long ll;
ll f[2][26 * 9];
ll GCD(ll a, ll b) { return b == 0 ? a : GCD(b, a%b); }
int main()
{
	int n, x;
	while(scanf("%d %d", &n, &x), n || x) {
		int cur = 1;
		memset(f, 0, sizeof(f));
		f[0][0] = 1;

		for(int i = 1; i <= n; i++)	{	//group
			for(int j = 0; j <= 6*n; j++)	//
				for(int k = 1; k <= 6; k++)	//items
					f[cur][j+k] += f[1-cur][j];
			cur = 1 - cur;
			memset(f[cur], 0, sizeof(f[cur]));
		}
		ll ans = 0;
		for(int i = x; i <= 6*n; i++) ans += f[1-cur][i];
		ll t   = 1, d = 1;
		for(int i = 1; i <= n; i++) {
			t *= 6;
			if(( d = GCD(t, ans) ) != 1) t /= d, ans /= d;
		}
		if(ans == 0) puts("0");
		else if(t == 1 && ans == 1) puts("1");
		else printf("%lld/%lld\n", ans, t);
	}
	return 0;
}

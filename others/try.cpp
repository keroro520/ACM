// http://pat.zju.edu.cn/contests/ds/4-07
// 算法错了。。数据：1 3 3 5
//把题意改成：切一次的代价，长度n的木头，切一次切成x,y(x+y=n)，则该次的代价 = x * y，求最大代价.
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;
typedef		long long		ll;
bool f[55][500005], g[55][500005];
int ans = 0;

ll getNewSet(int i, int j, vector<int> & v)
{
	if(i == -1) return 0;
	if(g[i+1][j]) return (1LL << i) | getNewSet(i-1, j-v[i], v);
	return getNewSet(i-1, j, v);
}
void solve(vector<int> & v)
{
	int n = v.size(), sum = 0;
	if(n == 1) return ;

	memset(f, 0, sizeof f);
	//memset(g, 0, sizeof g);
	f[0][0] = true;
	for(int i = 0; i < n; i++) {
		for(int j = sum+v[i]; j >= 0; j--)
			f[i+1][j] = f[i][j], g[i+1][j] = 0;
		for(int j = sum; j >= 0; j--)
			if(f[i][j] && !f[i+1][j+v[i]]) f[i+1][j+v[i]] = true, g[i+1][j+v[i]] = 1;
		sum += v[i];
	}

	ans += sum;

	double mid = sum*0.5;
	int res = 999999999;
	for(int j = 1; j < sum; j++) 
		if(fabs(j-mid) >= fabs(res-mid)) break;
		else if(f[n][j]) res = j;
	ll x = getNewSet(n-1, res, v);
	vector<int> v1, v2;
	for(int i = 0; i < n; i++) if(x & (1LL << i)) v1.push_back(v[i]); else v2.push_back(v[i]);
	solve(v1), solve(v2);
}
int main()
{
	int x, n;
	while(scanf("%d", &n) != EOF) {
		vector<int> v;
		for(int i = 0; i < n; i++) scanf("%d", &x), v.push_back(x);
		sort(v.begin(), v.end());
		
		ans = 0;
		solve(v);
		printf("%d\n", ans);
	}
	return 0;
}

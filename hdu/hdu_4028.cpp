/*
	离散化DP   好题  
	题意：给出1-N这N个数，问有多少个子集，集合里的lcm是大于等于m的

	思路：
		  子集虽然很多，但lcm不会太多。
		  其实就是不断加点不断扩展不断更新啦。。哪有什么DP啊。。。
		  我一开始是用一个map来保存着所有lcm，然后对于每个i不断更新，可是这样做欠考虑了一点！我是假设当前map里存的是之前所有lcm的话，我新加一个i，那不就是i跟这些lcm继续更新吗。。。但！这样的。。。。等一下。。。我觉得没错啊。。。。我再搞搞看。。。。
		  。。。啊。。没错没错。。搞出啦了，是刚才写搓了。。。虽然TLE了。。。加上预处理就AC了~~其实我想的跟下面写的是一个思路。。。。
		  作为纪念，下面也记一下吧。。。。=_=
*/
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;
typedef		long long		ll;
map<ll,ll> dp[45];
ll m, n;

ll GCD(ll x, ll y)
{
	return y == 0 ? x : GCD(y, x%y);
}
ll LCM(ll x, ll y)
{
	return x / GCD(x,y) * y;
}
void init()
{
	n = 40;
	dp[1][1] = 1;
	for(ll i = 2; i <= n; i++) {
		dp[i] = dp[i-1];
		dp[i][i] ++;
		for(map<ll,ll> :: iterator it = dp[i-1].begin(); it != dp[i-1].end(); it++)
			dp[i][ LCM(it->first, i) ] += it->second;
	}
}
int main()
{
	init();
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d %I64d", &n, &m);
		ll ans = 0;
		for(map<ll,ll> :: iterator it = dp[n].begin(); it != dp[n].end(); it++)
			if(it->first >= m) ans += it->second;
		printf("Case #%d: %I64d\n", ++Cas, ans);
	}
	return 0;
}





/*
void init()
{
	n = 40;
	M.clear();
	M[1] = 1;
	dp[1] = M;
	for(ll i = 2; i <= n; i++) {
		v.clear();
		for(map<ll,ll> :: iterator it = M.begin(); it != M.end(); it++) {
			v.push_back( Pii(LCM(i, it->first), (it->second)) );
		}
		M[i]++;
		for(vector<Pii> :: iterator it = v.begin(); it != v.end(); it++) {
			M[it->first] += it->second;
		}
		dp[i] = M;
	}
}


*/

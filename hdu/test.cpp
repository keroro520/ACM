/*
	离散化DP   好题  启发题
	题意：给出1-N这N个数，问有多少个子集，集合里的lcm是大于等于m的

	思路：

		  子集虽然很多，但lcm不会太多。
		  我一开始是用一个map来保存着所有lcm，然后对于每个i不断更新，可是这样做欠考虑了一点！我是假设当前map里存的是之前所有lcm的话，我新加一个i，那不就是i跟这些lcm继续更新吗。。。但！这样的。。。。等一下。。。我觉得没错啊。。。。我再搞搞看。。。。
*/
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;
typedef		long long		ll;
typedef		pair<ll,ll> 	Pii;
map<ll,ll> M, dp[45];
vector< Pii > v;
ll m, n;

ll GCD(ll x, ll y)
{
	return y == 0 ? x : GCD(y, x%y);
}
ll LCM(ll x, ll y)
{
	return x / GCD(x,y) * y;
}
void init();
int main()
{
	init();
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%I64d %I64d", &n, &m);
		ll ans = 0;
		for(map<ll,ll> :: iterator it = dp[n].begin(); it != dp[n].end(); it++) {
			if(it->first >= m) ans += it->second;
		}
		printf("Case #%d: %I64d\n", ++Cas, ans);
	}
	return 0;
}
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

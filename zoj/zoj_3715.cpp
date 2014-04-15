/*
	枚举然后贪心判定  好题
	题意：n个人从1到n编号，每个人可以投一票但是不能投给自己。1号是主角，想做班长，但票数必须严格大于其他人，但是主角可以任何人，收买每个人都有一个代价。求主角做到班长的最小花费。注意主角一开始没有投票，它可以选择投给任何人除开自己

	思路：思路：主角的票一定是投给当前票数最少的人，这样对他的影响最小。
	另外主角最后当选班长，他拥有的票数为v的话，其他人的票数必须全部 <= v-1，如果全部人的票数<=v-1的情况下，主角的票数已经>v，那么这个枚举是失败的（因为我们是假定主角的票数确切为v），然后将其他票拉过来给主角的时候，就贪心地选。


	没心情写题解了...这道水题硬是卡了我好久...最后还是对拍找出来的bug
	我一开始是直接让1号投给票数最少的那位同学，这是没错的，但问题是，不能在贪心判定之前就投！甩个数据，懒得说:
	4
	4 3 2 
	46 167 927 

	直接不管1号的票就ok了

	还有一点，收买的同学必须是原本没有投给1号的的同学，这点要判断一下，网上有个别人的程序是错的，但数据水了吧，让过了，but it's wrong
*/
#include <functional>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define		MAXN		105
#define		Pii			pair<int,int> 
typedef		long long 	ll;
struct Kid {
	int id, cost;
} kid[MAXN];
int n, vote[MAXN];
vector<Pii> v[MAXN];

bool cmp_by_cost(const Kid & a, const Kid & b) {
	return a.cost < b.cost;
}
void hash(int x, ll * tmp) {
	if(x < 60) tmp[0] |= (1LL << x);  else tmp[1] |= (1LL << (x - 60));
}
bool get (int x, ll * tmp) {
	if(x < 60) return tmp[0] & (1LL << x);  else return tmp[1] & (1LL << (x - 60));
}
int  calc(int _std)
{
	int ans = 0, rest = _std - v[1].size();
	ll tmp[2] = {0, 0};
	for(int i = 2; i <= n; i++) if(v[i].size() >= _std) {
		int k = v[i].size() - _std + 1;
		if( (rest -= k) < 0 ) return (1 << 29);
		for(vector<Pii> :: iterator it = v[i].begin(); it != v[i].end() && k; it++, k--)
			ans += it->first, hash(it->second, tmp);
	}
	
	for(int i = 2; i <= n && rest; i++) if(!get(kid[i].id, tmp) && vote[kid[i].id] != 1) {		//
		rest--;
		ans += kid[i].cost;
	}
	return ans;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) v[i].clear();
		for(int i = 2; i <= n; i++) scanf("%d", &vote[i]);
		for(int i = 2; i <= n; i++) scanf("%d", &kid[i].cost), kid[i].id = i;
		for(int i = 2; i <= n; i++) v[ vote[i] ].push_back( Pii(kid[i].cost, i) );

		int _min = 2, ans = (1 << 29);
		//for(int i = 2; i <= n; i++) if(v[_min].size() > v[i].size()) _min = i;
		//v[ _min ].push_back( Pii((1 << 29), 1) );

		for(int i = 1; i <= n; i++) sort(v[i].begin(), v[i].end());
		
		sort(kid+2, kid+1+n, cmp_by_cost);

		for(int i = v[1].size(); i < n; i++) ans = min(ans, calc(i));
		printf("%d\n", ans);
	}
	return 0;
}

/*
	树状数组 离线查询  维护最值  好题  启发题
	题意：序列{A}, ai < 2^31，若干询问[l,r]，回答区间内“从右端开始第一个出现过两次的数”，注意，是从区间右端开始扫

	思路：这道题比较新的地方在于，树状数组的值是原序列的下标，是维护最值，也就是下标最值
		  Updtae(L[i] , L[i])	

		  Neko说这道题很有启发性.....做成一眼题了....
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
using namespace std;
#define		Pii			pair<int,int>
#define		MAXN		500005
#define		low(x)		((x) & (-(x)))
int n, L[MAXN], a[MAXN], ans[MAXN/10], c[MAXN];
map<int,int> M;
vector<Pii> Q[MAXN];

void init()
{
	memset(c, 0, sizeof(c));
	for(int i = 1; i <= n; i++) Q[i].clear();
	M.clear();
	for(int i = 1; i <= n; i++) {
		int res = M[ a[i] ];
		L[i] = res ? res : -1;
		M[ a[i] ] = i;
	}
}
void Update(int pos, int val)
{
	while(pos) {
		c[pos] = max(c[pos], val);
		pos -= low(pos);
	}
}
int  Query(int pos)
{
	int res = 0;
	while(pos <= n) {
		res = max(res, c[pos]);
		pos += low(pos);
	}
	return res;
}
void solve()
{
	for(int i = 1; i <= n; i++) {
		if(L[i] != -1) Update(L[i], L[i]);
		for(vector<Pii> :: iterator it = Q[i].begin(); it != Q[i].end(); it++)
			ans[it->second] = a[Query(it->first)];
	}
}
int main()
{
	int l, r, query;
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		init();
		scanf("%d", &query);
		for(int i = 0; i < query; i++) {
			scanf("%d %d", &l, &r);
			Q[r].push_back( Pii(l, i) );
		}
		solve();
		for(int i = 0; i < query; i++) 
			if(ans[i] == 0) printf("OK\n"); else printf("%d\n", ans[i]);
		puts("");
	}
	return 0;
}

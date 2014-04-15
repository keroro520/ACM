/*
	二分图匹配 + 二分枚举  好题
	题意：在一个n*n的矩阵中，找n个数使得这n个数都在不同的行和列里并且要求这n个数中的最大值和最小值的差值最小。
	思路：二分差值，然后枚举最小值，再用二分图匹配判断是否可行
		  
		  真的好难想到用二分图匹配来写喔，太强了。
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		105
#define		inf			999999999
int vis[MAXN], a[MAXN][MAXN], link[MAXN];
int _min, _max, n, when, A, B;
bool dfs(int u)
{
	for(int i = 1; i <= n; i++) if(A <= a[u][i] && a[u][i] <= B) {
		if(vis[i] == when) continue;
		vis[i] = when;
		if(link[i] == -1 || dfs(link[i])) {
			link[i] = u;
			return true;
		}
	}
	return false;
}
int  max_match()
{
	memset(link, -1, sizeof link);
	for(int i = 1; i <= n; i++) {
		when++;
		if(!dfs(i)) return false;
	}
	return true;
}
bool check(int diff)
{
	for(int i = _min; i+diff <= _max; i++) {
		A = i, B = i + diff;
		if(max_match()) return true;
	}
	return false;
}
int main()
{
	int cases;
	scanf("%d", &cases);
	while(cases--) {
		int l = inf, r = -inf;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]), l = min(l, a[i][j]), r = max(r, a[i][j]);
		if(n == 1) { printf("%d\n", l); continue ;}
		int ans; 
		_min = l, _max = r;
		r = r - l, l = 0;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(check(mid)) ans = mid, r = mid - 1;
			else 		   l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

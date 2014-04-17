#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define			MAXN		1048676
int n, N;
long long equ[25], rev[25], Bits[25];		//TODO
int a[MAXN];
vector<int> v;

void calc(int x, int e)
{
	int l = 0, r = v.size() - 1, ans = -1;
	while(l <= r) {
		int mid = ((l + r) >> 1);
		if(v[mid] < x) {
			ans = mid, l = mid + 1;
		} else r = mid - 1;
	}
	rev[e] += ans + 1;
	for(ans++; ans < v.size() && v[ans] == x; ans++) equ[e]++;			//TODO
}
void dfs(int s, int e)
{
	if(e == 1) {
		rev[e] += a[s] >  a[s+1];
		equ[e] += a[s] == a[s+1];
		return ;
	}

	dfs(s, e-1), dfs(s + Bits[e-1], e-1);

	v.clear();
	for(int i = s + Bits[e-1]; i < s + Bits[e]  ; i++) v.push_back(a[i]);
	sort(v.begin(), v.end());

	for(int i = s; i < s+Bits[e-1]; i++) calc(a[i], e);
}
int main()
{
	Bits[0] = 1;
	for(int i = 1; i <= 20; i++) Bits[i] = Bits[i-1] * 2;
	int queries, q;
	scanf("%d", &n);
	N = (1 << n);		//TODO
	for(int i = 0; i < N; i++) scanf("%d", &a[i]);
	if(n > 0) dfs(0, n);		// TODO

	//for(int i = 1; i <= n; i++) printf("~~  %d %d %d\n",i,  rev[i], equ[i]);
	
	scanf("%d", &queries);
	while(queries--) {
		scanf("%d", &q);
		for(int i = 1; i <= q; i++) {
			rev[i] = Bits[n-i] * Bits[i-1]*Bits[i-1] - rev[i] - equ[i];			//eql
		}
		long long ans = 0;
		for(int i = 1; i <= n; i++) ans += rev[i];
		printf("%I64d\n", ans);
	}
	return 0;
}

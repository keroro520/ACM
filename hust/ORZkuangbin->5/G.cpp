#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define		MAXN		1005
struct Seg {
	int l, r;
} a[MAXN];
int n;

bool cmp(const Seg & a, const Seg & b) {
	if(a.r != b.r) return a.r < b.r;
	return a.l < b.l;
}
int main()
{
	while( scanf("%d", &n) != EOF ) {
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &a[i].l, &a[i].r); 
			if(a[i].l > a[i].r) swap(a[i].l, a[i].r);
		}
		sort(a, a+n, cmp);
		int pre = -(1 << 28);
		vector<int> ans;
		for(int i = 0; i < n; i++) {
			if(a[i].l <= pre && pre <= a[i].r) continue;
			pre = a[i].r, ans.push_back(pre);
		}
		printf("%d\n", ans.size());
		for(int i = 0; i < ans.size(); i++) printf("%d%c", ans[i], i == ans.size()-1? '\n' : ' ');
	}
	return 0;
}

#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MID(l,r)	(((l)+(r)) >> 1)
#define		MAXN		105
int a[MAXN], Q[MAXN], f[MAXN] , g[MAXN];
int top, n;
int find(int x)
{
	int l = 0, r = top-1, ans = top;
	while(l <= r) {
		int mid = MID(l, r);
		if(x <= Q[mid]) ans = mid, r = mid - 1; //l = mid+1;
		else l = mid + 1;
	}
	return ans;
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		top = 0;
		for(int i = 1; i <= n; i++) {
			int j = find(a[i]);
			if(j == top) Q[top++] = a[i];
			else Q[j] = a[i];
			f[i] = j + 1;
		}
		top = 0;
		for(int i = n; i > 0; i--) {
			int j = find(a[i]);
			if(j == top) Q[top++] = a[i];
			else Q[j] = a[i];
			g[i] = j + 1;
		}
		int ans = n;
		for(int i = 1; i <= n; i++) 
			ans = min(ans, n + 1 - f[i] - g[i]);
		printf("%d\n", ans);
	}
	return 0;
}

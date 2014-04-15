#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		100005
int a[MAXN], f[MAXN], Q[MAXN];
int n, top;
int Find(int x)
{
	int l = 1, r = top-1, ans = top;
	while(l <= r) {
		int mid = ((l + r) >> 1);
		if(Q[mid] > x) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	top = 1;
	for(int i = 1; i <= n; i++) {
		int j = Find(a[i]);
		if(j == top) Q[top++] = a[i];
		else Q[j] = a[i];
		f[i] = j;
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) ans = max(f[i], ans);
	//if(ans < 2) ans = 0;
	printf("%d\n", ans);
	return 0;
}

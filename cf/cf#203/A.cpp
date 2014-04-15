#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		105
int n, m;
int a[MAXN], b[MAXN];

int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) scanf("%d", &b[i]);
	sort(a, a+n), sort(b, b+m);

	if(a[n-1] >= b[0] || a[0]*2 >= b[0]) {
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= 100; i++)
		if(i >= a[0]*2 && i >= a[n-1]) {
			printf("%d\n", i);
			return 0;
		}
	return 0;
}

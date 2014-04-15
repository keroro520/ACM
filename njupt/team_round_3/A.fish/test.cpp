#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN	100005
int a[MAXN], b[MAXN];
int n, m, k;
bool cmp(const int a, const int b)
{
	return a > b;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &k) != EOF) {
		
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		for(int i = 0; i < m; i++) scanf("%d", &b[i]);
		if(n > m) {
			printf("YES\n");
			continue;
		}
		sort(a, a+n, cmp), sort(b,b+m, cmp);
		bool flag = false;
		for(int i = 0; i < n; i++) if(a[i] > b[i]) {
			flag = true;
			break;
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}

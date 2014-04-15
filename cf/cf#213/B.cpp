#include <stdio.h>
#include <algorithm>
using namespace std;
long long a[100005];
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%I64d", &a[i]);

	int ans = 0, sum = 2;
	if(n >= 2) ans = 2;
	else if(n >= 1) ans = 1;

	for(int i = 2; i < n; i++) {
		if(a[i] == a[i-1] + a[i-2]) sum++;
		else sum = 2;
		ans = max(ans, sum);
	}
	printf("%d\n", ans);
	return 0;
}

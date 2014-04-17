#include <stdio.h>
#include <algorithm>
using namespace std;

int n;
int people[105];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &people[i]);

	int ans = 999999999;
	for(int i = 1; i <= n; i++) {
		int time = 0, x;
		for(int j = 1; j <= people[i]; j++) {
			scanf("%d", &x);
			time += x*5 + 15;
		}
		ans = min(ans, time);
	}
	printf("%d\n", ans);
	return 0;
}

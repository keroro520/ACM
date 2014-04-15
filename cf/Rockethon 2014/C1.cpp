#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		105
int p[MAXN], e[MAXN];

int n, K, inf = 999999999;
int calc(int stat)
{
	int effect = 0, point = 0, rant = 0;
	for(int i = 0; i < n; i++) if(stat & (1 << i)) effect += e[i], point ++; else p[i]++;
	for(int i = 0; i < n; i++) if(point < p[i] || (point == p[i] && (0 == (stat & (1 << i))))) rant++;
	for(int i = 0; i < n; i++) if(0 == (stat & (1 << i))) p[i]--;
	return rant >= K ? inf : effect;
}
int main()
{
	int ans = inf;
	scanf("%d %d", &n, &K);
	for(int i = 0; i < n; i++) scanf("%d %d", &p[i], &e[i]);
	for(int i = 0, oo = (1<<n); i < oo; i++) {
		ans = min(ans, calc(i));
	}
	if(ans == inf) ans = -1;
	printf("%d\n", ans);
	return 0;
}

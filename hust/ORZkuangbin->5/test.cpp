#include <stdio.h>
#include <string.h>
#define	MAXN	105
bool vis[MAXN];
int  dis[MAXN], a[MAXN][MAXN], power[MAXN];
int K, n;
int  prime(int s)
{
	memset(vis, false, sizeof vis);
	memset(dis,   127, sizeof dis);
	for(int i = 0; i < K; i++) dis[power[i]] = 0;

	int ans = 0;
	while(true) {
		int _mini, _min = (1 << 28);
		for(int i = 1; i <= n; i++) if(!vis[i] && dis[i] < _min) {
			_min = dis[i], _mini = i;
		}
		if(_min == (1 << 28)) return ans;
		ans += _min; vis[_mini] = true;
		for(int i = 1; i <= n; i++) if(a[_mini][i] < dis[i]) dis[i] = a[_mini][i];
	}
}
int main()
{
	while(scanf("%d %d", &n, &K) != EOF) {
		for(int i = 0; i < K; i++) scanf("%d", &power[i]);
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);

		printf("%d\n", prime(0));
	}
	return 0;
}

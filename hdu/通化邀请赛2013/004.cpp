#include <stdio.h>
#define		MAXN	10005
#define		MAXM	100005
int edge[MAXM][2], ans[MAXM], father[MAXN];

int Find(int x) { x == father[x] ? x : father[x] = Find(father[x]); }
void Union(int x, int y)
{
	father[x] = y;
}
void work(int n, int m)
{
	for(int i = 0; i < m; i++) {
		scanf("%d%d", &edge[i][0], &edge[i][1]);
	}
	for(int i = 0; i < n; i++) father[i] = i;
	ans[m] = n;
	for(int i = m-1; i >= 0; i--) {
		int x = Find(edge[i][0]), y = Find(edge[i][1]);
		if(x == y) ans[i] = ans[i+1];
		else {
			ans[i] = ans[i+1] - 1;
			Union(x, y);
		}
	}
	for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}
int main()
{
	int m, n;
	while(scanf("%d%d", &n, &m) != EOF) {
		work(n, m);
	}
	return 0;
}

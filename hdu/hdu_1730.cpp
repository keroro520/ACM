/*
	博弈 简单sg
*/
#include <string.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define		MAXN		105
int sg[MAXN];

int SG(int n)
{
	if(n == 0) return 0;
	if(sg[n] != -1) return sg[n];
	bool vis[MAXN];
	memset(vis, false, sizeof vis);
	for(int i = 1; i <= n; i++) vis[SG(n-i)] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[n] = i;
}
int main()
{
	int n, m;
	memset(sg, -1, sizeof(sg));
	while(scanf("%d %d", &n, &m) != EOF) {
		int ans = 0, x, y;
		while(n--) {
			scanf("%d %d", &x, &y);
			x = abs(y - x) - 1;
			ans ^= SG(x);
		}
		puts(ans ? "I WIN!" : "BAD LUCK!");
	}
	return 0;
}

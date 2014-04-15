/*
	完全背包裸题 DP
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		INF		2139062143
#define		MAXN	505
int weight[MAXN], value[MAXN], f[10005];

int main()
{
	int E, F, n, cases;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d%d", &E, &F);
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d%d", &value[i], &weight[i]);
		memset(f, 127, sizeof(f));
		f[0] = 0;
		int m = F - E;
		for(int i = 1; i <= n; i++)
			for(int j = weight[i]; j <= m; j++)
				f[j] = min(f[j], f[j-weight[i]] + value[i]);
		if(f[m] == INF) puts("This is impossible.");
		else printf("The minimum amount of money in the piggy-bank is %d.\n", f[m]);
	}
	return 0;
}

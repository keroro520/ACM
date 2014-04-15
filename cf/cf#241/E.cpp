/*
	图论  最短路

	题意：无向带边权图，任意两点之间最多一条边。要求输出所有点对s->t的最多路所经过的所有边数。

	深觉这道题的解法很妙啊. 写了个n*n*m的TLE了，想了很久不会做，看了大牛的代码，自己理解了一下。

	[*] 先Floyd 求出所有(s,t)的最短路                    //我当初写了个n * dijstra 是作了多大的死，虽说复杂度确实比Floyd有降
	[*] 算出cnt[i][j] 表示i->j的最短路上有多少条i的邻接边
	[*] 最后i->j的最短路经过的边数ans[i][j] 就等于 i->j最短路途径的所有点k的cnt[k][j]之和

	是怎么想到cnt[i][j]这样的表示的呢？ 求告知啊！
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define		MAXN		505
int e[MAXN][MAXN], dist[MAXN][MAXN], cnt[MAXN][MAXN];
int n, m;

int main()
{
	scanf("%d %d", &n, &m);

	memset(dist, 0x3F, sizeof dist);
	for(int i = 1; i <= n; i++) dist[i][i] = 0;
	for(int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		e[u][v] = e[v][u] = dist[u][v] = dist[v][u] = w;
	}

	for(int k = 1; k <= n; k++)
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) if(e[i][j]) {
			for(int k = 1; k <= n; k++)
				if(e[i][j] + dist[j][k] == dist[i][k]) cnt[i][k]++;
		}

	for(int i = 1; i <= n; i++)
		for(int j = i+1; j <= n; j++) {
			int ans = 0;
			for(int k = 1; k <= n; k++)
				if(dist[i][k] + dist[k][j] == dist[i][j])
					ans += cnt[k][j];
			printf("%d ", ans);
		}
	puts("");
	return 0;
}

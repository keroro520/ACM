#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define			MAXN		105
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
struct Cell {
	int x, y, h;
} a[MAXN * MAXN];
int pos[MAXN][MAXN], head[MAXN * MAXN], f[MAXN * MAXN], in[MAXN*MAXN], Q[MAXN*MAXN];
struct Edge {
	int v, next;
} edge[MAXN * MAXN * 4];
int idx, edge_num;
bool cmp(const Cell & a, const Cell & b) {
	return a.h < b.h;
}
void add_edge(int u, int v) 
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof head);
	memset(in  ,  0, sizeof in  );
	memset(f,     0, sizeof f   );
}
int  solve()
{
	int car = 0, cdr = 0, ans = 0;
	for(int i = 0; i < idx; i++) if(!in[i]) f[i] = 1, Q[car++] = i;
	while(cdr < car) {
		int u = Q[cdr++];
		if(head[u] == -1) ans += f[u];
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			f[v] += f[u];
			if(--in[v] == 0) Q[car++] = v;
		}
	}
	return ans;
}
int main()
{
	int cases, Cas = 0, n, m;
	scanf("%d", &cases);
	while(cases--) {
		init();
		scanf("%d %d", &n, &m);
		idx = 0;
		for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) scanf("%d", &a[idx].h), a[idx].x = i, a[idx].y = j, idx++;
		sort(a, a+idx, cmp);
		for(int i = 0; i < idx; i++) pos[a[i].x][a[i].y] = i;
		for(int i = 0; i < idx; i++) {
			int x = a[i].x, y = a[i].y, h = a[i].h;
			for(int d = 0; d < 4; d++) {
				int tx = x + dx[d], ty = y + dy[d];
				if(0 <= tx && tx < n && 0 <= ty && ty < m && a[pos[tx][ty]].h < a[i].h) {
					add_edge(tx*m+ty, x*m+y);
					in[x*m+y]++;
				}
			}
		}
		int ans = solve();
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}

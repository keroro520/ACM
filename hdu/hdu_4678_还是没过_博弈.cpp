//hdu 4678  还是没过
#include <stdio.h>
#include <string.h>
#define		MAXN	1005
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int Q[MAXN * MAXN][2], chess[MAXN][MAXN], sg[MAXN * MAXN];		
int n, m;

bool check(int x, int y)
{
	return 0 <= x && x < n && 0 <= y && y < m;
}
void label(int x, int y)
{
	chess[x][y] = -1;
	for(int i = 0; i < 8; i++) {
		int tx = x + dx[i], ty = y + dy[i];
		if(check(tx, ty) && chess[tx][ty] != -1) chess[tx][ty] = 1;
	}
}
void init()
{
	memset(chess, 0, sizeof(chess));
}
int  dye(int sx, int sy)
{
	int top = 1, tail = 0, sum = 0;
	bool exist_space = false;
	Q[top][0] = sx, Q[top][1] = sy;
	chess[sx][sy] = -1;
	while(tail < top) {
		int x = Q[tail][0], y = Q[tail][1];
		tail++;
		for(int i = 0; i < 8; i++) {
			int tx = x + dx[i], ty = y + dy[i];
			if(check(tx, ty) && chess[tx][ty] != -1) {
				if(chess[tx][ty] == 1) {
					sum ++;
				} else {
					exist_space = true;
					Q[top][0] = tx, Q[top][1] = ty;
					top++;
				}
				chess[tx][ty] = -1;
			}
		}
	}
	return sum;//+ exist_space;
}
int SG(int u)
{
	if(u == 0) return 0;
	if(sg[u] != -1) return sg[u];
	int res = SG(u - 1);
	if(res == 0 || res == 2) return sg[u] = 1;
	else if(res == 1) return sg[u] = 2;
}
int main()
{
	int cases, Cas = 0, mines, x, y;
	scanf("%d", &cases);
	memset(sg, -1, sizeof(sg));
	while(cases--) {
		scanf("%d%d%d", &n, &m, &mines);
		init();
		for(int i = 0; i < mines; i++) {
			scanf("%d%d", &x, &y);
			label(x, y);
		}
		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) if(chess[i][j] == 0) {
				ans ^= (dye(i, j) & 1) ? 2 : 1;
//				ans ^= SG(dye(i, j));
			}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++) if(chess[i][j] == 1) ans ^= 1;
		printf("Case #%d: %s\n", ++Cas, ans == 0 ? "Fanglaoshi" : "Xiemao");
	}
	return 0;
}

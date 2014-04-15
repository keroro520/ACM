#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
#define		MAXX		2005
#define		MAXN		2005
#define		Limit		10003
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
struct Point {
	int x, y;
	Point() { }
	Point(int x, int y) : x(x), y(y) { } 
} A, B, p[MAXN], Q[205 * 205 * 5];
map<int,int> M;
int b[2*MAXN], color[MAXX][MAXX], f[MAXX][MAXX];
bool vis[MAXX][MAXX];
int top, MX, MY;

bool arrive()
{
	memset(vis, false, sizeof vis);
	int car = 0, cdr = 0;
	Q[car++] = Point(A.x,A.y);
	while(cdr != car) {
		Point u = Q[(cdr++) % Limit];
		if(u.x == B.x && u.y == B.y) return true;
		for(int d = 0; d < 4; d++) {
			int tx = u.x + dx[d], ty = u.y + dy[d];
			if(0 <= tx && tx <= MX && 0 <= ty && ty <= MY && color[tx][ty] < 2 && !vis[tx][ty]) 
				Q[(car++)%Limit] = Point(tx,ty), vis[tx][ty] = true;
		}
	}
	return false;
}
void dye()
{
	memset(color, 0, sizeof color);
	for(int i = 2; i < top; i += 2) {
		int j = i + 1;
		int min_x = min(p[i].x,p[j].x), max_x = max(p[i].x,p[j].x);
		int min_y = min(p[i].y,p[j].y), max_y = max(p[i].y,p[j].y);
		for(int x = min_x+1; x < max_x; x++)	
			for(int y = min_y+1; y < max_y; y++) 
				color[x][y] = 2;
		for(int x = min_x; x <= max_x; x++) color[x][min_y]++, color[x][max_y]++;
		for(int y = min_y; y <= max_y; y++) color[min_x][y]++, color[max_x][y]++;
		color[min_x][min_y]--, color[min_x][max_y]--, color[max_x][min_y]--, color[max_x][max_y]--;
	}
	//for(int i = 0; i < top; i++) printf("(%d %d)\n", p[i].x,p[i].y);
}
void solve()
{
	memset(f, 127, sizeof f);
	memset(vis, 0, sizeof vis);
	f[A.x][A.y] = 0;
	
	int &ans = f[B.x][B.y];
	int car = 0, cdr = 0;
	Q[car++] = Point(A.x,A.y);
	while(cdr != car) {
		Point u = Q[(cdr++) % Limit];  int x = u.x, y = u.y;  
		vis[x][y] = false;
		if(f[x][y] + 1 >= ans) continue;
	
		for(int d = 0; d < 4; d++) {
			int tx = x + dx[d], ty = y + dy[d];
			while(0 < tx && tx <= MX && 0 < ty && ty <= MY && color[tx][ty] < 2 ) {
				if(f[tx][ty] > f[x][y] + 1) {
					f[tx][ty] = f[x][y] + 1;
					if(!vis[tx][ty]) vis[tx][ty] = true, Q[(car++)%Limit] = Point(tx,ty);
				}
				tx += dx[d], ty += dy[d];
			}
		}
	}
}

int main()
{
	int n,x1,y1,x2,y2;
	while(scanf("%d %d %d %d", &A.x, &A.y, &B.x, &B.y), A.x || A.y || B.x || B.y) {
		top = 0;
		p[top++] = A, p[top++] = B;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			p[top++] = Point(x1,y1), p[top++] = Point(x2,y2);
		}
		if(A.x == B.x && A.y == B.y) { puts("0"); continue; }
		for(int i = 0; i < top; i++) b[i] = p[i].x;
		sort(b, b+top);
		M.clear();  int tmp = 3;
		M[b[0]] = 1;
		for(int i = 1; i < top; i++) if(b[i] != b[i-1]) M[b[i]] = (tmp += 3);
		for(int i = 0; i < top; i++) p[i].x = M[p[i].x];
		A.x = M[A.x], B.x = M[B.x];
		MX = tmp + 3;

		for(int i = 0; i < top; i++) b[i] = p[i].y;
		sort(b, b+top);
		M.clear();  tmp = 3;
		M[b[0]] = 1;
		for(int i = 1; i < top; i++) if(b[i] != b[i-1]) M[b[i]] = (tmp += 3);
		for(int i = 0; i < top; i++) p[i].y = M[p[i].y];
		A.y = M[A.y], B.y = M[B.y];
		MY = tmp + 3;

		dye();
		if(!arrive()) puts("-1");
		else solve(), printf("%d\n", f[B.x][B.y] - 1);
	}
	return 0;
}

/*
  线性DP   滑雪
  因为初始化WA了一次，要初始化为1，而不是无穷小
  思路：按高度h排序一遍，记录每个(x,y)在排序后的位置，然后按高度序列扫一遍，扫到(x,y)时，
        能从(x-1,y),(x+1,y),(x,y-1),(x,y+1)状态转移，根据坐标找到相应的位置即可
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 505
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
struct Grid {
  int x, y, h;
  Grid() {}
  Grid(int x, int y, int h) : x(x), y(y), h(h) {}
  bool operator < (const Grid & b) const {
    return h < b.h;
  }
} a[MAXN*MAXN];
int pos[MAXN][MAXN], f[MAXN*MAXN];
int idx = 0, n, m;
int main()
{
  int h;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) {
      scanf("%d", &h);
      a[idx++] = Grid(i, j, h);
    }
  sort(a, a+idx);
  for(int i = 0; i < idx; i++) pos[a[i].x][a[i].y] = i;

  for(int i = 0 ; i < idx; i++) f[i] = 1;   //因为初始化WA了一次
  int ans = 0;
  for(int i = 1; i < idx; i++) {
    int x = a[i].x, y = a[i].y;
    for(int d = 0; d < 4; d++) {
      int tx = x + dx[d], ty = y + dy[d];
      if(!(0 <= tx && tx < n && 0 <= ty && ty < m)) continue;
      int p = pos[tx][ty];
      if(p < i && a[p].h < a[i].h) f[i] = max(f[i], f[p] + 1);
    }
    ans = max(ans, f[i]);
  }
  printf("%d\n", ans);
  return 0;
}

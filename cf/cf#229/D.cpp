// 思路题
// 先从近到远铺，输出的时候从远到近铺
// 没啥考头。还是C比较好玩
#include <vector>
#include <queue>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef 	pair<int,int> Pii;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
queue< Pii > Q;
vector< Pii > ans;
int n, m, K;
int c[100][100];
void output(int x, int y, int tx, int ty) {
	if(x == tx && y == ty) {
		printf("(%d,%d)\n", x, y);
		return ;
	} else {
		if(x + 1 <= tx) {
			printf("(%d,%d) ", x, y);
			output(x+1, y, tx, ty);
		} else {
			printf("(%d,%d) ", x, y);
			output(x, y+1, tx, ty);
		}
	}
}
int main()
{
	int plenty = 0;
	scanf("%d %d %d", &n, &m, &K);
	Q.push( Pii(1,1) ); c[1][1] = 1;
	while(ans.size() < K) {
		ans.push_back( Q.front() );
		int x = Q.front().first, y = Q.front().second;   Q.pop();
		plenty += x + y - 1;
		for(int i = 0; i < 4; i++) {
			int tx = x + dx[i], ty = y + dy[i];
			if(c[tx][ty] == 0 && 0 < tx && 0 < ty && tx <= n && ty <= m) {
				c[tx][ty] = 1, Q.push( Pii(tx,ty) );
			}
		}
	}
	printf("%d\n", plenty);
	for(int i = K-1; i >= 0; i--) {
		output( 1, 1, ans[i].first, ans[i].second );
		//printf("%d  %d\n" , ans[i].first, ans[i].second);
	}
	return 0;
}

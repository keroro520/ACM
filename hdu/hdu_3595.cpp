/*
	博弈  every-sg every-nim  SG

	题意:题目有N个游戏同时进行，每个游戏有两堆石子，每次从个数多的堆中取走数量小的数量的整数倍的石子。取最后一次的获胜。并且N个游戏同时进行，除非游戏结束，否则必须操作。 


	思路：用sg搞。网上多为直接根据性质搞，不会，找到了这个用sg搞的。



	以下摘自：http://blog.sina.com.cn/s/blog_51cea4040100h3l9.html
 	于是我们开一个Step数组。
    表示对于先手必胜的单一游戏而言，它最少走好多步胜利。对于先手必败的单一游戏而言，它最多走好多步。
    这样，我们只需要看最后所有单一游戏最大的step那组的SG是0还是非0就可以断定是否先手必胜了。
 
    很容易得出：
    （u是v的子状态）
    step[v] = 0；                 （v为终止状态）
    step[v] = max{step[u]} + 1；  （sg[v]>0,sg[u]=0）
    step[v] = min{step[u]} + 1；  （sg[v]==0）

*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN		1005
int sg[MAXN][MAXN], step[MAXN][MAXN];

int SG(int x, int y)
{
	int ans1 = 0, ans2 = 999999999;
	if(x > y) swap(x, y);
	if(x == 0) return 0;
	if(sg[x][y] != -1) return sg[x][y];
	for(int i = x; i <= y; i += x) {
		if(!SG(x, y-i)) {
			ans1 = max(ans1, step[x][y-i] + 1);
			sg[x][y] = sg[y][x] = 1;
		} else ans2 = min(ans2, step[x][y-i] + 1);
	}
	if(sg[x][y] == 1) {
		step[x][y] = step[y][x] = ans1;
		return 1;
	} else {
		sg[x][y] = sg[y][x] = 0;
		step[x][y] = step[y][x] = ans2;
		return 0;
	}
}

int main()
{
	int x, y, n;
	memset(sg, -1, sizeof(sg));
	while(scanf("%d", &n) != EOF) {
		int ans1 = 0, ans2 = 0;
		while(n--) {
			scanf("%d%d", &x, &y);
			if(SG(x, y)) ans1 = max(ans1, step[x][y]);
			else ans2 = max(ans2, step[x][y]);
		}
		puts(ans1 > ans2 ? "MM" : "GG");
	}
	return 0;
}
